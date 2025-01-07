#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define SHM_NAME "my_shm"
#define SHM_SIZE 4096

typedef struct {
	int request_type;
	int arg1;
	int arg2;
	int result;
} rpc_request;

void server() {
	int shm_fd;
	rpc_request *shm_ptr;
	
	// Create or open shared memory
	shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	if (shm_fd == -1) {
		perror("shm_open");
		exit(1);
	}
	
	// Set size of shared memory
	if (ftruncate(shm_fd, SHM_SIZE) == -1) {
		perror("ftruncate");
		exit(1);
	}
	
	// Map shared memory to process address space
	shm_ptr = (rpc_request *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_ptr == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	
	while (1) {
		// Wait for client request
		while (shm_ptr->request_type == 0) {
			sleep(1); // Wait for request
		}
		
		// Process request
		switch (shm_ptr->request_type) {
			case 1: // Add
				shm_ptr->result = shm_ptr->arg1 + shm_ptr->arg2;
				break;
			case 2: // Subtract
				shm_ptr->result = shm_ptr->arg1 - shm_ptr->arg2;
				break;
			case 3: // Multiply
				shm_ptr->result = shm_ptr->arg1 * shm_ptr->arg2;
				break;
			case 4: // Divide
				if (shm_ptr->arg2 != 0) {
					shm_ptr->result = shm_ptr->arg1 / shm_ptr->arg2;
				} else {
					shm_ptr->result = 0; // Handle division by zero
				}
				break;
			default:
				shm_ptr->result = -1; // Invalid request
		}

		// Indicate result is ready
		shm_ptr->request_type = 0;
		
		if (shm_ptr->request_type == -1)
			break;
	}
	
	// Unmap and close
	if (munmap(shm_ptr, SHM_SIZE) == -1) {
		perror("munmap");
	}
	close(shm_fd);
}

void client() {
	int shm_fd;
	rpc_request *shm_ptr;
	
	// Open existing shared memory
	shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
	if (shm_fd == -1) {
		perror("shm_open");
		exit(1);
	}
	
	// Map shared memory to process address space
	shm_ptr = (rpc_request *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_ptr == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	
	// Send requests
	shm_ptr->request_type = 1; // Add
	shm_ptr->arg1 = 5;
	shm_ptr->arg2 = 3;
	while (shm_ptr->request_type != 0) {
		sleep(1); // Wait for server to process
	}
	printf("Result of 5 + 3 = %d\n", shm_ptr->result);
	
	shm_ptr->request_type = 2; // Subtract
	shm_ptr->arg1 = 10;
	shm_ptr->arg2 = 4;
	while (shm_ptr->request_type != 0) {
		sleep(1);
	}
	printf("Result of 10 - 4 = %d\n", shm_ptr->result);
	
	// Unmap and close
	if (munmap(shm_ptr, SHM_SIZE) == -1) {
		perror("munmap");
	}
	close(shm_fd);
}


void run() {
	int rnum = 100;
	
	int * ptr1 = (int*) malloc(sizeof(int));
	
	ioctl(0, 100);
	
	int * ptr2 = NULL;

	srand( (unsigned) time(NULL));
	while (true) {
		rnum = rand() % 255;
		if (rnum == 100) {
			*ptr2  = rnum;
		} else {
			*ptr1 = rnum;
		}
		printf("Random number: %d \n", rnum);
		usleep(10000);
	}
}
