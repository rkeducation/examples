// main.cpp
//

#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <thread>

#include "tcp/include/runner.hpp"
#include "tensors/include/tensor.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
	// ---- main ----
	
	// Start of program
	printf("Starting program....\n");
	
	run_task_loop();
	
	// End of program
	printf("Ending program....\n");
	
	
	tensor<int> t = { 1, 2, 3, 4, 5 };

	return 0;
}
