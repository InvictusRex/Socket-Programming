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

char *resolve_ip(char *buffer) {
  buffer[strcspn(buffer, "\n")] = '\0';
  char *hostname = (char *)malloc(strlen(buffer));
  strcpy(hostname, buffer);
  printf("Hostname: %s\n", hostname);
  struct addrinfo hints, *res;
  char ip[BUFFER_SIZE];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  int result = getaddrinfo(hostname, NULL, &hints, &res);
  if (result != 0) {
    return strdup("Error resolving IP");
  }
  struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
  inet_ntop(AF_INET, &(ipv4->sin_addr), ip, INET_ADDRSTRLEN);

  return strdup(ip);
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
    char *ip = resolve_ip(buffer);
    send(socket, ip, strlen(ip), 0);
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