#pragma once

#include <cstdio>


namespace json
{

class CStdAllocator
{
public:
    static void free(auto* addr) noexcept;

	[[nodiscard("Memory allocated via malloc must be released")]]
	static void* malloc(std::size_t n);

	[[nodiscard("Memory allocated via malloc must be released")]]
    static auto* realloc(auto* addr, std::size_t oldSize, std::size_t newSize);
};

}// namespace json

// Include template implementation
#include <BetterJson/Implementations/CStdAllocator.tpp>
