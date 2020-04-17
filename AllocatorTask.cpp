// Task.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "map"
#include <iostream>
#include "Allocator.cpp"

int main()
{
	Allocator* all = new Allocator((size_t)100);
	void* point = all->alloc((size_t)50);
	std::cout << point << "\n";
	point = all->alloc((size_t)25);
	std::cout << point << "\n";
	all->dealloc(point);
	return 0;
}
