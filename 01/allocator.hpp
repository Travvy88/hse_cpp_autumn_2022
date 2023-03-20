#pragma once

#include <iostream>

class Allocator
{
public:
    char *data = nullptr;
    char *offset;
    size_t max_size;
    size_t allocated_size;

    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    // Это деструктор!
    ~Allocator();
};
