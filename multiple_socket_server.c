#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8001
#define BUFFER_SIZE 1024
#define N 5

void cleanup(int socket) { close(socket); }

int setup_server() {
  int server_fd;
  struct sockaddr_in address;
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  int binding = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
  listen(server_fd, 3);
  printf("Socket initialised\n");
  return server_fd;
}

void communication(int socket) {
  char buffer[BUFFER_SIZE] = {0};

  for (int i = 0; i < N; i++) {
    memset(buffer, 0, BUFFER_SIZE);
    recv(socket, buffer, BUFFER_SIZE, 0);
    printf("Message: %s\n", buffer);
  }
}

int main(void) {
  struct sockaddr_in address;
  int addr_len = sizeof(address);
  int server_fd = setup_server();

  while (1) {
    int client =
        accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len);
    pid_t pid = fork();
    if (pid == 0) {
      cleanup(server_fd);
      communication(client);
      cleanup(client);
    } else {
      cleanup(server_fd);
    }
  }
  return 0;
}

