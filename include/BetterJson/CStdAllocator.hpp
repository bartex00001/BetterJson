#pragma once

#include <cstdio>

#include <BetterJson/Allocator.hpp>


namespace json
{

class CStdAllocator : public Allocator
{
public:
	[[nodiscard("Memory allocated via malloc must be released")]]
	void* malloc(std::size_t n) override;

	[[nodiscard("Memory allocated via malloc must be released")]]
    void* realloc(void* addr, std::size_t oldSize, std::size_t newSize) override;

	void free(void* addr) noexcept override;
};

}// namespace json
