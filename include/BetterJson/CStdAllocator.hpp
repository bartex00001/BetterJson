#pragma once

namespace json
{

class CStdAllocator
{
    void* malloc(size_t n);
    void* realloc(void* addr, size_t oldSize, size_t newSize);
    static void free(void* addr);
};

}// namespace json
