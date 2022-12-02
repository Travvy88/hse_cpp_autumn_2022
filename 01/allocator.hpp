#pragma once

#include <iostream>

class Allocator
{
public:
    char *data = nullptr;
    size_t offset;
    size_t max_size;

    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    // Это деструктор!
    ~Allocator();
};
