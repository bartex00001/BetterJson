#include <cstdlib>
#include <new>
#include <iostream>

#include <BetterJson/CStdAllocator.hpp>


namespace json
{

inline void CStdAllocator::free(auto* addr) noexcept
{
	std::free(addr);
}

inline void* CStdAllocator::malloc(std::size_t n)
{
	void* res{std::malloc(n)};
	if(res == nullptr) [[unlikely]]
		throw std::bad_alloc();

	return res;
}

inline auto* CStdAllocator::realloc(auto* addr, std::size_t oldSize, std::size_t newSize)
{
	void* res{std::realloc(addr, newSize)};
	if(res == nullptr) [[unlikely]]
		throw std::bad_alloc();

	return reinterpret_cast< decltype(addr) >(res);
}

}// namespace json