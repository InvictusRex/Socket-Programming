#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Simple XOR-based CRC function
unsigned char calculate_crc(const char *data) {
    unsigned char crc = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        crc ^= data[i];
    }
    return crc;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0), new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    char message[BUFFER_SIZE] = {0};
    unsigned char received_crc;
    
    // Receive message
    recv(new_socket, message, BUFFER_SIZE, 0);

    // Receive CRC
    recv(new_socket, &received_crc, sizeof(received_crc), 0);

    // Calculate CRC on received message
    unsigned char calculated_crc = calculate_crc(message);
    printf("Received message: %s\n", message);
    printf("Received CRC: %u\n", received_crc);
    printf("Calculated CRC: %u\n", calculated_crc);

    // Check if CRC matches
    if (calculated_crc == received_crc) {
        printf("No error detected.\n");
    } else {
        printf("Error detected in the received message.\n");
    }

    close(new_socket);
    close(server_fd);
    return 0;
}