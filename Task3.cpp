// Task3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>	

template <typename T>
class SmartPointer {
public:
	T* object;
	int count_of_ref;

	SmartPointer(T* obj) {
		object = obj;
		count_of_ref = 1;
	}

	T* get() {
		return object;
	}

	void set(T* new_object) {
		object = new_object;
		count_of_ref++;
	}

	void release() {
		count_of_ref--;
		if (count_of_ref == 0)
			delete object;
	}

	SmartPointer& operator=(SmartPointer& other) {
		if (this == &other)
			return *this;
		release();
		return *this;
	}

	T* operator->() {
		return object;
	}

	T* operator*() {
		return *object;
	}
};


int main()
{
	SmartPointer<int> pointer = new int(1);
	SmartPointer<int> other_pointer = new int(0);
	pointer = other_pointer;	
	pointer.release();
	pointer.set(new int(2));
}

