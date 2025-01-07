//
//  tcp.cpp
//  SysHealth
//
//  Created by Ramesh Kumar on 07/01/25.
//

#include <iostream>
#include <cstring>
#include <netinet/ip.h>  // For struct iphdr
#include <netinet/tcp.h> // For struct tcphdr
#include <arpa/inet.h>   // For inet_ntoa
#include <sys/socket.h>
#include <unistd.h>

// Buffer size for packets
constexpr int BUFFER_SIZE = 65536;

