#pragma once

#include <cstdint>


namespace json
{

class Allocator
{
public:
	virtual void* malloc(std::size_t n) = 0;
	virtual void* realloc(void* addr, std::size_t oldSize, std::size_t newSize) = 0;
	virtual void free(void* addr) noexcept = 0;

	virtual ~Allocator() = default;
};

}//namespace json
