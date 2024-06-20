#pragma once

#include <cstring>

#include <BetterJson/Definitions.hpp>
#include <BetterJson/MemoryPool.hpp>


namespace json
{

template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
void MemoryPool< TAllocator >::addChunk(std::size_t n)
{
	void* newChunk{allocator.malloc(n)};
	last->next = reinterpret_cast< ChunkHeader* >(newChunk);
	last = last->next;

	*last = ChunkHeader{
		.size = sizeof(ChunkHeader),
		.capacity = static_cast< std::uint32_t >(n)
	};
}

template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
void* MemoryPool< TAllocator >::allocate(std::size_t n)
{
	void* address{reinterpret_cast< char* >(last) + last->size};
	last->size += n;
	return address;
}


template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
bool MemoryPool< TAllocator >::canFitAlloc(std::size_t n) const
{
	return last->capacity > last->size + n;
}

template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
bool MemoryPool< TAllocator >::isLastElement(const void* addr, std::size_t elementSize) const
{
	return reinterpret_cast< char* >(last) + last->size - elementSize == addr;
}

template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
constexpr bool MemoryPool< TAllocator >::largerThanChunk(std::size_t n)
{
	return n >= BETTER_JSON_CHUNK_SIZE + sizeof(ChunkHeader);
}


template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
MemoryPool< TAllocator >::MemoryPool()
	: allocator(TAllocator())
{
	first = last = reinterpret_cast< ChunkHeader* >(
		allocator.malloc(BETTER_JSON_CHUNK_SIZE)
		);

	*first = ChunkHeader{
		.size = sizeof(ChunkHeader),
		.capacity = BETTER_JSON_CHUNK_SIZE
	};
}

template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
MemoryPool< TAllocator >::~MemoryPool() noexcept
{
	while((last = first) != nullptr)
	{
		first = first->next;
		allocator.free(last);
	}
}

template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
MemoryPool< TAllocator >::MemoryPool(MemoryPool&& mp) noexcept
{
	this->first = mp.first;
	this->last = mp.last;

	mp.first = mp.last = nullptr;
}


template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
MemoryPool< TAllocator >& MemoryPool< TAllocator >::operator=(MemoryPool&& mp) noexcept
{
	ChunkHeader* temp{};
	while((temp = this->first) != nullptr)
	{
		this->first = this->first->next;
		allocator.free(temp);
	}

	this->first = mp.first;
	this->last = mp.last;

	mp.first = mp.last = nullptr;

	return *this;
}


template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
void MemoryPool< TAllocator >::free(void* addr [[maybe_unused]]) noexcept
{
	// Do not free on call - all chunks will be released on object destruction
}

template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
void* MemoryPool< TAllocator >::malloc(std::size_t n)
{
	if(!canFitAlloc(n)) [[unlikely]]
	{
		const std::size_t newSize{largerThanChunk(n)
			? n
			: BETTER_JSON_CHUNK_SIZE
		};

		addChunk(newSize);
	}

	return allocate(n);
}

template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
void* MemoryPool< TAllocator >::realloc(void* addr, std::size_t oldSize, std::size_t newSize)
{
	if(addr == nullptr)
		return this->malloc(newSize);

	// Smaller size? no modification needed
	if(newSize <= oldSize)
	{
		if(isLastElement(addr, oldSize))
			last->size -= oldSize - newSize;

		return addr;
	}

	// Resized element will fit inside current chunk? adjust the bounds without copy
	if(isLastElement(addr, oldSize) && canFitAlloc(newSize - oldSize))
	{
		last->size += newSize - oldSize;
		return addr;
	}

	// Last element and the chunk is large? realloc in place (possibly avoid copy)
	if(isLastElement(addr, oldSize) && largerThanChunk(newSize))
		return allocator.realloc(last, last->size, last->size + newSize - oldSize);

	// Allocate new memory and copy old contents
	void* newPtr{this->malloc(newSize)};
	return std::memcpy(newPtr, addr, oldSize);
}

}// namespace json
