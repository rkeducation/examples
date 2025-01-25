// main.cpp
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include "tcp/include/runner.hpp"

int main() {

    int status = run_server_for_raw_data();
    
    return status;
}
