#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8001
#define BUFFER_SIZE 1024
#define N 5

void cleanup(int socket) { close(socket); }

int setup_client() {
  int sock;
  struct sockaddr_in address;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

  int connection = connect(sock, (struct sockaddr *)&address, sizeof(address));
  printf("Socket initialised\n");
  return sock;
}

void communication(int socket) {
  char buffer[BUFFER_SIZE] = {0};

  for (int i = 0; i < N; i++) {
    memset(buffer, 0, BUFFER_SIZE);
    printf("Message: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    send(socket, buffer, BUFFER_SIZE, 0);
  }
}

int main(void) {
  int client = setup_client();
  communication(client);
  cleanup(client);
  return 0;
}