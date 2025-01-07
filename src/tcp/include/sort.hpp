//
//  sort.hpp
//  SysHealth
//
//  Created by Ramesh Kumar on 18/12/24.
//

#ifndef sort_hpp
#define sort_hpp

// ---------------------- MERGE SORT -------------------------

template <typename Type>
void merge(Type * arr, size_t begin, size_t mid, size_t end) {
	// Merge arrays into sorted array
	size_t len = end - begin + 1;
	if (len == 0) return; // Ignore the sorting
	
	Type temp[len];
	for (size_t idx = 0; idx < len; idx++)
	{
		temp[idx] = arr[begin + idx];
	}
	
	// itr for array
	size_t pos = begin;
	
	end = end - begin;
	mid = mid -  begin;
	begin = begin - begin;
	
	size_t index1 = begin;
	size_t index2 = mid+1;
	
	while ( index1 <= mid && index2 <= end )
	{
		if (temp[index1] <= temp[index2]) {
			arr[pos++] = temp[index1++];
		}
		else {
			arr[pos++] = temp[index2++];
		}
	}
	while (index1 <= mid)
	{
		arr[pos++] = temp[index1++];
	}
	while (index2 <= end)
	{
		arr[pos++] = temp[index2++];
	}
}

template <typename Type>
void merge_sort(Type * arr, size_t begin, size_t end) {
	if (begin >= end)
		return;
	size_t mid = begin + (end - begin) / 2;
	merge_sort(arr, begin, mid);
	merge_sort(arr, mid+1, end);
	merge(arr, begin, mid, end);
}

// ---------------------- MERGE SORT -------------------------


#endif
