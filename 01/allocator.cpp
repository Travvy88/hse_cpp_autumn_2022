#include "allocator.hpp"
#include <iostream>

void
Allocator::makeAllocator(size_t maxSize)
{	
	if (data == nullptr){
		delete[] data;
	}
	offset = 0;
	max_size = maxSize;
	char *data = new char[maxSize]; 
}

char*
Allocator::alloc(size_t size)
{
   if (offset + size > max_size) {
	return nullptr;
   }
   else {
	offset  = offset + size;
	return data + offset;
   }
  
}

void
Allocator::reset()
{
   offset = 0;
}

Allocator::~Allocator() 
{
	delete[] data;
}

int main_() {
	int a = 0;
	Allocator al;
	al.makeAllocator(10);
	char *res = al.alloc(5);
	char *res_ = al.alloc(6);
	return 0; }
