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
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    char message[BUFFER_SIZE];
    printf("Enter a message: ");
    scanf("%[^\n]", &message) ; // Remove newline

    // Calculate CRC
    unsigned char crc = calculate_crc(message);
    printf("Original CRC: %u\n", crc);

    // Option to introduce an error
    char choice;
    printf("Introduce an error? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        message[0] ^= 1;  // Flip a bit to introduce an error
    }

    // Send message and CRC to server
    send(sock, message, strlen(message), 0);
    send(sock, &crc, sizeof(crc), 0);

    close(sock);
    return 0;
}