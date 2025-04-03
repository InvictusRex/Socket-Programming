#include <stdio.h>
#include <math.h>

// Function to print an IP address in dotted decimal format
void printIP(unsigned int ip) {
    printf("%u.%u.%u.%u", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

int main() {
    unsigned int baseIP[4], ipInt = 0, hostCount, newPrefix, increment, maxHosts, mask;
    char ipClass;

    // Input the classful IP address
    printf("Enter the classful IP address (e.g., 192.168.1.0): ");
    scanf("%u.%u.%u.%u", &baseIP[0], &baseIP[1], &baseIP[2], &baseIP[3]);

    // Determine the class and default prefix
    unsigned int firstOctet = baseIP[0];
    int defaultPrefix;
    if (firstOctet >= 1 && firstOctet <= 126) {
        ipClass = 'A';
        defaultPrefix = 8;
    } else if (firstOctet >= 128 && firstOctet <= 191) {
        ipClass = 'B';
        defaultPrefix = 16;
    } else if (firstOctet >= 192 && firstOctet <= 223) {
        ipClass = 'C';
        defaultPrefix = 24;
    } else {
        printf("Invalid IP class.\n");
        return 1;
    }

    // Convert IP to a single integer for calculation
    ipInt = (baseIP[0] << 24) | (baseIP[1] << 16) | (baseIP[2] << 8) | baseIP[3];

    // Input the number of hosts required per subnet
    printf("Enter the number of hosts needed per subnet: ");
    scanf("%u", &hostCount);

    // Calculate the new prefix based on host requirements
    int requiredBits = (int)ceil(log2(hostCount + 2)); // +2 for network and broadcast addresses
    newPrefix = 32 - requiredBits;

    if (newPrefix < defaultPrefix) {
        printf("Error: Not enough addresses in the given classful block to create subnets.\n");
        return 1;
    }

    // Calculate the increment for each subnet
    increment = pow(2, requiredBits);
    maxHosts = increment - 2; // Exclude network and broadcast

    // Display the subnets
    printf("\nClass %c Subnets:\n", ipClass);
    unsigned int subnetCount = pow(2, newPrefix - defaultPrefix); // Total possible subnets
    for (unsigned int i = 0; i < subnetCount; i++) {
        unsigned int startIP = ipInt + (i * increment);
        unsigned int endIP = startIP + increment - 1;

        // Calculate subnet mask
        mask = ~((1 << (32 - newPrefix)) - 1);

        printf("Subnet %u: ", i + 1);
        printIP(startIP);
        printf(" - ");
        printIP(endIP);
        printf(" /%u (Max hosts: %u)\n", newPrefix, maxHosts);
    }

    return 0;
}