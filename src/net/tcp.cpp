//
//  tensor.cpp
//  SysHealth
//
//  Created by Ramesh Kumar on 21/12/24.
//

#include <string>
#include <vector>

#include "include/tcp.hpp"

inline int XOR(int a, int b)
{
	return a ^ b;
}

bool doesValidArrayExist(std::vector<int> & derived) {
	int N = (int) derived.size();
	std::vector<int> src(N, 0);
	
	int i = 0;
	
	int oldstep = 0;
	
	while ( i < N ) {
		int j = (i+1) % N;
		if ( derived[i] == XOR(src[i], src[j] ) ) {
			i++;
		}
		else {
			if ( j == 0 || j == oldstep ) return false;
			src[j] = !(src[j]);
			oldstep = j;
		}
	}
	
	return true;
}

void example1() {
	
	std::vector<int> derived = { 1, 0 };
	
	printf("RESULT = %d \n", doesValidArrayExist(derived));
	
}
