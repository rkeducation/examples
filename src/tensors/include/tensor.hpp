//
//  tensor.hpp
//  SysHealth
//
//  Created by Ramesh Kumar on 21/12/24.
//

#ifndef tensor_hpp
#define tensor_hpp

#include <iostream>
#include <vector>
#include <functional>
#include <cstring>

template <class Type>
class tensor {

	class d_shape {
		int *data;
		int length;
		
	public:
		~d_shape () {
			delete data;
		}
		d_shape (int length) {
			length = (int) 1;
			data = new int (length);
			*data = length;
		}
		
		d_shape (int * arr, int len) {
			data = new int(len);
			memcpy(data, arr, len);
			length = len;
		}
		d_shape (d_shape & sh) {
			data = new int(sh.count());
			memcpy(data, sh.data, sh.count());
			length = sh.length;
		}
		inline int count() {
			int res = 1;
			for (int itr = 0; itr < length; itr++)
				res *= data[itr];
			return res;
		}
	};

public:
	// initialize with data
	tensor (const std::initializer_list<Type> _list) {
		int total = (int) _list.size();
		data = new Type[total];
		memcpy(data, _list.begin(), total * sizeof(Type));
		shape = new d_shape(total);
	}
	// initialize with raw data and shape
	tensor (Type * _ptr, d_shape *_shape) {
		data = _ptr;
		shape = _shape;
	}
	// Copy constructor
	tensor (tensor<Type> & t) {
		data = new Type[t.shape->count() * sizeof(Type)];
		shape = t.shape;
	}
	~tensor () {
		delete [] data;
		delete shape;
	}
	
	template <typename RetType>
	class Transform {
	public:
		std::function<RetType (Type)> fn;
		Transform (std::function<RetType (Type)> _tr) {
			fn = _tr;
		}
	};

private:
	// pointer to data buffer
	Type * data;

	// shape of the tensor
	d_shape *shape;
};


#endif /* tensor_hpp */
