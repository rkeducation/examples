// main.cpp
//

#include <cstddef>
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include "tcp/include/runner.hpp"

int main(int argc, char *argv[]) {

  // create a socket
  int sockfd = socket(AF_PACKET, SOCK_RAW, 0x0003);
  if (sockfd < 0) {
    perror("Error in socker creation");
    return 1;
  }

  printf("<----> Socket created <---->");
  int result = getsockopt(sockfd, 1, 0, NULL, NULL);
  if (result < 0) {
    perror("Sockopt error");
    return result;
  }
  printf("Socketoption = %d \n", result);

  return 0;
}
