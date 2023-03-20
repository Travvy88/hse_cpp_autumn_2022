#include "allocator.hpp"
#include <iostream>

void
Allocator::makeAllocator(size_t maxSize)
{
    delete[] data;
    allocated_size = 0;
	max_size = maxSize;
	char *data = new char[maxSize];
    char *offset = data;
}

char*
Allocator::alloc(size_t size)
{
    char *to_return;
    if (allocated_size + size <= max_size) {
       to_return = offset;
       offset += size;
       allocated_size += size;
       return to_return;
    }
    else {
        return nullptr;
    }
}

void
Allocator::reset()
{
   offset = data;
   allocated_size = 0;
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
