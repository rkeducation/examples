//
//  health.hpp
//  SysHealth
//
//  Created by Ramesh Kumar on 16/12/24.
//

#ifndef health_hpp
#define health_hpp

#include <stdio.h>

// Function to calculate CPU usage
void getCpuUsage() ;

// Function to get memory usage
void getMemoryUsage() ;

// Function to get connected hardware information using lshw command
void getHardwareInfo() ;

void * initialize_shared_memory();

#endif /* health_hpp */
