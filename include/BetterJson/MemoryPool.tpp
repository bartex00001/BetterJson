#pragma once

#include <BetterJson/MemoryPool.hpp>


namespace json
{

template< Allocator TAllocator >
void MemoryPool<TAllocator>::free(void* addr)
{
	// Do nothing :D
}

template< Allocator TAllocator >
void* MemoryPool< TAllocator >::malloc(std::size_t n)
{
	return allocator.malloc(n);
}


template< Allocator TAllocator >
std::size_t MemoryPool< TAllocator >::size() const
{
	return chunkCount * BETTER_JSON_CHUNK_SIZE;
}

}// namespace json
