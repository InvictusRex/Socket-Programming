#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define N 5

int setup()
{
    int server_fd;
    struct sockaddr_in address;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int binding = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("Setup finished\n");
    return server_fd;
}

int communication(int socket)
{
    char buffer[BUFFER_SIZE] = {0};

    for (int i=0; i<N; i++)
    {
        memset(buffer, BUFFER_SIZE, 0);
        recv(socket, buffer, BUFFER_SIZE, 0);
        printf("Message: %s\n", buffer);
    }
}

int main(void)
{
    struct sockaddr_in address;
    int addr_len = sizeof(address);

    int server_fd = setup();
    int client = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len);
    communication(client);
    close(client);
    close(server_fd);
}