//
//  health.cpp
//  SysHealth
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <sys/fcntl.h>

#ifdef __APPLE__
#include <sys/sysctl.h> // macOS-specific
#include <mach/mach.h>  // For memory usage
#endif

using namespace std;

// Cross-platform macro for clearing the terminal
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Function to get CPU usage
void getCpuUsage() {
#ifdef __linux__
	// Linux CPU usage
	ifstream file("/proc/stat");
	if (!file) {
		cerr << "Error: Unable to open /proc/stat" << endl;
		return;
	}
	
	string line;
	getline(file, line); // Read the first line (CPU stats)
	istringstream iss(line);
	
	string cpuLabel;
	long user, nice, system, idle, iowait, irq, softirq, steal;
	iss >> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
	
	long totalIdleTime = idle + iowait;
	long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;
	
	// Sleep for 1 second to measure CPU usage over time
	this_thread::sleep_for(chrono::seconds(1));
	
	ifstream file2("/proc/stat");
	getline(file2, line); // Read the updated CPU stats
	istringstream iss2(line);
	
	long user2, nice2, system2, idle2, iowait2, irq2, softirq2, steal2;
	iss2 >> cpuLabel >> user2 >> nice2 >> system2 >> idle2 >> iowait2 >> irq2 >> softirq2 >> steal2;
	
	long totalIdleTime2 = idle2 + iowait2;
	long totalTime2 = user2 + nice2 + system2 + idle2 + iowait2 + irq2 + softirq2 + steal2;
	
	double idleDelta = totalIdleTime2 - totalIdleTime;
	double totalDelta = totalTime2 - totalTime;
	double cpuUsage = (1.0 - (idleDelta / totalDelta)) * 100.0;
	
	cout << "CPU Usage: " << cpuUsage << " %" << endl;

#elif __APPLE__
	// macOS CPU usage
	int mib[2] = {CTL_HW, HW_NCPU};
	int ncpu;
	size_t len = sizeof(ncpu);
	
	if (sysctl(mib, 2, &ncpu, &len, nullptr, 0) == 0) {
		cout << "Number of CPU Cores: " << ncpu << endl;
	} else {
		cerr << "Error: Unable to get CPU cores." << endl;
	}
#endif
}

// Function to get memory usage
void getMemoryUsage() {
#ifdef __linux__
	ifstream file("/proc/meminfo");
	if (!file) {
		cerr << "Error: Unable to open /proc/meminfo" << endl;
		return;
	}
	
	string line;
	long totalMemory = 0, availableMemory = 0;
	
	while (getline(file, line)) {
		istringstream iss(line);
		string key;
		long value;
		string unit;
		
		iss >> key >> value >> unit;
		
		if (key == "MemTotal:") totalMemory = value;
		if (key == "MemAvailable:") availableMemory = value;
		
		if (totalMemory > 0 && availableMemory > 0) break;
	}
	
	long usedMemory = totalMemory - availableMemory;
	
	cout << "Total Memory: " << totalMemory / 1024 << " MB" << endl;
	cout << "Used Memory: " << usedMemory / 1024 << " MB" << endl;
	cout << "Available Memory: " << availableMemory / 1024 << " MB" << endl;
	
#elif __APPLE__
	// macOS Memory usage
	int64_t totalMemory, freeMemory;
	size_t len = sizeof(totalMemory);
	
	// Get total memory
	if (sysctlbyname("hw.memsize", &totalMemory, &len, nullptr, 0) == 0) {
		cout << "Total Memory: " << totalMemory / (1024 * 1024) << " MB" << endl;
	} else {
		cerr << "Error: Unable to get total memory." << endl;
	}
	
	// Get free memory using mach API
	mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
	vm_statistics64_data_t vm_stat;
	kern_return_t result = host_statistics64(mach_host_self(), HOST_VM_INFO, (host_info64_t)&vm_stat, &count);
	
	if (result == KERN_SUCCESS) {
		freeMemory = (vm_stat.free_count + vm_stat.inactive_count);  /** sysconf(_SC_PAGESIZE);*/
		cout << "Free Memory: " << freeMemory / (1024 * 1024) << " MB" << endl;
	} else {
		cerr << "Error: Unable to get free memory." << endl;
	}
#endif
}

// Function to get connected hardware information
void getHardwareInfo() {
#ifdef __linux__
	cout << "Connected Hardware Information (Linux):" << endl;
	int result = system("lshw -short");
	if (result != 0) {
		cerr << "Error: 'lshw' not installed. Install it using 'sudo apt install lshw'." << endl;
	}
#elif __APPLE__
	cout << "Connected Hardware Information (macOS):" << endl;
	int result = system("system_profiler SPHardwareDataType SPStorageDataType SPNetworkDataType");
	if (result != 0) {
		cerr << "Error: Unable to retrieve hardware information." << endl;
	}
#endif
}
