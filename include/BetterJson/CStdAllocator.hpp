#pragma once

#include <cstdio>


namespace json
{

class CStdAllocator
{
public:
    static void free(void* addr) noexcept;

	[[nodiscard("Memory allocated via malloc must be released")]]
	static void* malloc(std::size_t n);

	[[nodiscard("Memory allocated via malloc must be released")]]
    static void* realloc(void* addr, std::size_t oldSize, std::size_t newSize);
};

}// namespace json
