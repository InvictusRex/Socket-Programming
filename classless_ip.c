#include <stdio.h>
#include <math.h>

void printIP(unsigned int ip) {
    printf("%u.%u.%u.%u", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

int main() {
    unsigned int baseIP[4], ipInt = 0, subnetCount, newPrefix, increment, mask;
    int prefix;

    // Input the base IP block
    printf("Enter the IP block in CIDR notation (e.g., 192.168.1.0/24): ");
    scanf("%u.%u.%u.%u/%d", &baseIP[0], &baseIP[1], &baseIP[2], &baseIP[3], &prefix);

    // Convert IP to a single integer for calculation
    ipInt = (baseIP[0] << 24) | (baseIP[1] << 16) | (baseIP[2] << 8) | baseIP[3];

    // Input the number of required subnets
    printf("Enter the number of subnets required: ");
    scanf("%u", &subnetCount);

    // Calculate new prefix length
    newPrefix = prefix + (int)ceil(log2(subnetCount));
    if (newPrefix > 32) {
        printf("Error: Not enough bits to create the requested number of subnets.\n");
        return 1;
    }

    // Calculate the increment for each subnet
    increment = pow(2, 32 - newPrefix);

    // Display the subnets
    printf("\nSubnets:\n");
    for (unsigned int i = 0; i < subnetCount; i++) {
        unsigned int startIP = ipInt + (i * increment);
        unsigned int endIP = startIP + increment - 1;

        // Calculate subnet mask
        mask = ~((1 << (32 - newPrefix)) - 1);

        printf("Subnet %u: ", i + 1);
        printIP(startIP);
        printf(" - ");
        printIP(endIP);
        printf(" /%u\n", newPrefix);
    }

    return 0;
}