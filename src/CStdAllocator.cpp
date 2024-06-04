#include <cstdlib>
#include <new>
#include <iostream>

#include <BetterJson/CStdAllocator.hpp>


namespace json
{

void CStdAllocator::free(void* addr) noexcept
{
	std::free(addr);
}

void* CStdAllocator::malloc(std::size_t n)
{
	void* res{std::malloc(n)};
	if(res == nullptr) [[unlikely]]
		throw std::bad_alloc();

	return res;
}

void* CStdAllocator::realloc(void* addr, std::size_t oldSize, std::size_t newSize)
{
	void* res{std::realloc(addr, newSize)};
	if(res == nullptr) [[unlikely]]
		throw std::bad_alloc();

	return res;
}

}// namespace json