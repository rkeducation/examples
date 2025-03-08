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

  // Run task loop infinitely
  run_task_loop();
  return 0;
}
