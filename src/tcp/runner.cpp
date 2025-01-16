//
//  runner.cpp
//  SysHealth
//
//  Created by Ramesh Kumar on 07/01/25.
//


#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>

#include "include/client.hpp"
#include "include/runner.hpp"

// -----------------------------------------------------
// -----------------------------------------------------
int run_client ( const char * host, int port ) {
	
	Client cl(host, port);
	int status = cl.connect();

	if (status != 0) {
		return EXIT_FAILURE;
	}
	char msg[1024];
	msg[0] = 0;
	
	while (1) {
		std::string message;
		printf("\nInput Message > ");
		std::getline(std::cin, message);
		if (message == "exit") {
			break;
		}
		cl.send_message(message.c_str());
		
		// Wait for message
		cl.read_message_with_wait(msg, 1024);
		printf("Message : %s \n", msg);
		msg[0] = 0;
		sleep(1);
	}
	
	std::cout << "All clients stopped" << std::endl;
	return 0;
}


// -------------------------------------------------
// -------------------------------------------------
int run_server () {
	Server s;
	s.start();
	return 0;
}


// -------------------------------------------
// -------------------------------------------
int execute_command(std::string & command ) {
	if (command == "server") {
		return run_server();
	}
	else if (command == "client") {
		return run_client("127.0.0.1", 4433);
	}
	// return some error
	return 1;
}


// -----------------------------
// Convert char to lowercase
char to_lower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}


//  ------------------------------------
//  ------------------------------------
void run_task_loop() {
	std::string command;
	std::set<std::string> exit_commands = {
		"q", "quit", "exit"
	};
	while (true) {
		if (command.empty()) {
			printf("Input some command to execute > ");
			std::getline(std::cin, command);
		}
		std::transform(command.begin(), command.end(), command.begin(), to_lower);
		if (exit_commands.count(command) > 0 ) {
			break;
		}
		int status = execute_command(command);
		if (status == 0) {
			printf("Command executed: %s \n", command.c_str());
		}
		
		// clear command
		command.clear();
		
		// Sleep for 5 second and take another input
		sleep(2);
	}
}

// ===================================================
// ---------------------------------------------------
// ---------------------------------------------------

// Function to parse and display IP header information
void print_header_info(const struct ip* ipHeader) {

	// Extract information from the IP header
	std::cout << "IP Header Information:" << std::endl;
	std::cout << "Version: " << static_cast<int>(ipHeader->ip_v) << std::endl;
	std::cout << "Header Length: " << static_cast<int>(ipHeader->ip_hl * 4) << " bytes" << std::endl;
	std::cout << "Type of Service: " << static_cast<int>(ipHeader->ip_tos) << std::endl;
	std::cout << "Total Length: " << ntohs(ipHeader->ip_len) << " bytes" << std::endl;
	std::cout << "Identification: " << ntohs(ipHeader->ip_id) << std::endl;
	std::cout << "Fragment offset: " << ntohs(ipHeader->ip_off) << std::endl;

	std::cout << "TTL: " << static_cast<int>(ipHeader->ip_ttl) << std::endl;
	std::cout << "Protocol: " << static_cast<int>(ipHeader->ip_p) << std::endl;
	std::cout << "Checksum: " << ntohs(ipHeader->ip_sum) << std::endl;

	char srcIP[INET_ADDRSTRLEN];
	char destIP[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ipHeader->ip_src, srcIP, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &ipHeader->ip_dst, destIP, INET_ADDRSTRLEN);

	std::cout << "Source IP: " << srcIP << std::endl;
	std::cout << "Destination IP: " << destIP << std::endl;
}

int run_server_for_raw_data() {
 
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
        long bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &len);
        if (bytes_received == -1) {
            perror("recvfrom() failed");
            break;
        }
		const struct ip* ipHeader = reinterpret_cast<const struct ip*>(buffer);
		print_header_info(ipHeader);

		int header_len = static_cast<int>(ipHeader->ip_hl * 4);
		int total_len = ntohs(ipHeader->ip_len);
		buffer[total_len] = 0;
		printf("Total Bytes received: %d \n", total_len);
		printf("Header length: %d \n", header_len);
		printf("MSG : %s \n", buffer + header_len);
		std::cout << "---------------------------- \n\n" << std::endl;
    }

    close(sockfd);
    return 0;
}
