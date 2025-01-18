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

class IPPacket {
	
	/* Header information */
	struct ip * ip_header;
	
	/*  Store payload data, header is not included */
	char * payload;

public:
	/*  Constructor  */
	explicit IPPacket (const char * buffer);
	

	u_short payload_len() {
		return ip_header->ip_len - ip_header->ip_hl;
	}
	
	~IPPacket () {
		delete ip_header;
		delete payload;
	}
};


int start_packet_server();


#endif /* PACKET_HPP */
