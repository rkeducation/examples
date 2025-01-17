//
//  activation.cpp
//  SysHealth
//
//  Created by Ramesh Kumar on 22/12/24.
//

#include <iostream>

#include "include/ip_packet.hpp"


void initialize( const char * buffer ) {
	
	const struct ip * ip_header = reinterpret_cast<const struct ip*>(buffer);
	
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
	initialize(buffer);
}
