//
//  activation.hpp
//  SysHealth
//
//  Created by Ramesh Kumar on 22/12/24.
//

#ifndef PACKET_HPP
#define PACKET_HPP

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>

class packet {
	/*  Store payload data, header is not included */
	char * payload;
	
	/*  Header bytes data  */
	char * header;
		
public:
	packet (char * buffer);
	
};


#endif /* PACKET_HPP */
