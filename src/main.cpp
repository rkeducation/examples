// main.cpp
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>


int main() {
    // Create a raw socket
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if (sockfd == -1) {
        perror("socket() failed");
        return 1;
    }
    printf( "Create success \n");

    // Define the socket address structure
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // Receive packets for any source IP

    // Bind the socket to the interface
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind() failed");
        close(sockfd);
        return 1;
    }
    printf( "Bind success \n");

    // Receive IP packets
    char buffer[4096]; // Buffer to store received packets
    while (true) {
        socklen_t len = sizeof(addr);
        printf( "Waiting for packaets \n");
        int bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &len);
        if (bytes_received == -1) {
            perror("recvfrom() failed");
            break;
        }

        // Process the received IP packet here
        // ...
        
        printf("Bytes received: %d \n", len);

        // Example: Print the source and destination IP addresses
        std::cout << "Source IP: " << inet_ntoa(addr.sin_addr) << std::endl;
        // Extract destination IP from the received packet (in the IP header)
        // ...

    }

    close(sockfd);
    return 0;
}
