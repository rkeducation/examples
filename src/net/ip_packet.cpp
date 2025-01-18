//
//  activation.cpp
//  SysHealth
//
//  Created by Ramesh Kumar on 22/12/24.
//

#include <iostream>
#include <string>

#include "include/ip_packet.hpp"


void print_header_detail( const struct ip * ip_header ) {
		
	// Extract information from the IP header
	std::cout << "IP Header Information:" << std::endl;
	std::cout << "Version: " << static_cast<int>(ip_header->ip_v) << std::endl;
	std::cout << "Header Length: " << static_cast<int>(ip_header->ip_hl * 4) << " bytes" << std::endl;
	std::cout << "Type of Service: " << static_cast<int>(ip_header->ip_tos) << std::endl;
	std::cout << "Total Length: " << ntohs(ip_header->ip_len) << " bytes" << std::endl;
	std::cout << "Identification: " << ntohs(ip_header->ip_id) << std::endl;
	std::cout << "Fragment offset: " << ntohs(ip_header->ip_off) << std::endl;

	std::cout << "TTL: " << static_cast<int>(ip_header->ip_ttl) << std::endl;
	std::cout << "Protocol: " << static_cast<int>(ip_header->ip_p) << std::endl;
	std::cout << "Checksum: " << ntohs(ip_header->ip_sum) << std::endl;

	char srcIP[INET_ADDRSTRLEN];
	char destIP[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ip_header->ip_src, srcIP, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &ip_header->ip_dst, destIP, INET_ADDRSTRLEN);

	std::cout << "Source IP: " << srcIP << std::endl;
	std::cout << "Destination IP: " << destIP << std::endl;
}

IPPacket :: IPPacket(const char * buffer) {
	
	const struct ip * _header = reinterpret_cast<const struct ip*>(buffer);
	print_header_detail(_header);
	
	ip_header = (struct ip*) malloc(sizeof(struct ip));
	memcpy(ip_header, _header, sizeof(struct ip));
	
	u_short p_len = payload_len();
	payload = (char*) malloc(payload_len());
	memcpy(payload, buffer+_header->ip_hl, payload_len());
	
	// printing payload
	printf("\nPayload : \n");
	for (int i = 0; i < p_len; i+=2) {
		printf("0x%hX, ", payload[i]);
	}
}


int start_packet_server() {
	
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
	char buffer[65536]; // Buffer to store received packets
	while (true) {
		socklen_t len = sizeof(addr);
		printf( "Waiting for packets ... \n");
		long total_bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &len);
		if (total_bytes == -1) {
			perror("recvfrom() failed");
			break;
		}
		IPPacket packet = IPPacket(buffer);
		
		// printing bytes
		printf("Total Bytes received: %ld \n", total_bytes);
		printf("\n---------- BYTES IN HEX --------------\n");
		
		for (int i = 0; i < total_bytes; i+=2) {
			printf("0x%hx, ", buffer[i]);
		}

		printf("\n------------------------\n");
	}

	close(sockfd);
	return 0;
}
