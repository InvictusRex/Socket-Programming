#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8081
#define BUFFER_SIZE 1024
#define N 5

void cleanup(int socket) { close(socket); }

char *resolve_dns(char *buffer) {
  buffer[strcspn(buffer, "\n")] = '\0';
  char *ip = (char *)malloc(strlen(buffer));
  strcpy(ip, buffer);
  printf("IP: %s\n", ip);
  struct sockaddr_in sa;
  char host[BUFFER_SIZE];
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  inet_pton(AF_INET, ip, &sa.sin_addr);

  int result = getnameinfo((struct sockaddr *)&sa, sizeof(sa), host,
                           sizeof(host), NULL, 0, NI_NAMEREQD);

  if (result != 0) {
    return strdup("Error resolving hostname");
  }
  return strdup(host);
}

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
    char *host = resolve_dns(buffer);
    send(socket, host, strlen(host), 0);
  }
}

int main(void) {
  struct sockaddr_in address;
  int addr_len = sizeof(address);
  int server_fd = setup_server();
  int client =
      accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len);
  communication(client);
  cleanup(client);
  cleanup(server_fd);
  return 0;
}
