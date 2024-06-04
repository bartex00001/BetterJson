#pragma once

#include <cstring>

#include <BetterJson/MemoryPool.hpp>


namespace json
{

template< Allocator TAllocator >
void MemoryPool< TAllocator >::addChunk(std::size_t n)
{
	void* newChunk{allocator.malloc(n)};
	last->next = reinterpret_cast< ChunkHeader* >(newChunk);
	last = last->next;

	*last = ChunkHeader{
		.capacity = static_cast< std::uint32_t >(n)
	};
}

template< Allocator TAllocator >
void* MemoryPool< TAllocator >::allocate(std::size_t n)
{
	void* address{last + last->size + sizeof(ChunkHeader)};
	last->size += n;
	return address;
}


template< Allocator TAllocator >
bool MemoryPool< TAllocator >::canFitAlloc(std::size_t n) const
{
	return last->capacity > last->size + n;
}

template< Allocator TAllocator >
bool MemoryPool< TAllocator >::isLastElement(const void* addr, std::size_t elementSize) const
{
	return last + sizeof(ChunkHeader) + last->size - elementSize == addr;
}

template< Allocator TAllocator >
constexpr bool MemoryPool< TAllocator >::largerThanChunk(std::size_t n)
{
	return n >= BETTER_JSON_CHUNK_SIZE + sizeof(ChunkHeader);
}


template< Allocator TAllocator >
MemoryPool< TAllocator >::MemoryPool()
	: allocator(TAllocator())
{
	first = last = reinterpret_cast< ChunkHeader* >(
		allocator.malloc(BETTER_JSON_CHUNK_SIZE)
		);
}

template< Allocator TAllocator >
MemoryPool< TAllocator >::MemoryPool(char* buffer)
	: allocator(TAllocator()),
      fileBuffer(buffer)
{
	first = last = reinterpret_cast< ChunkHeader* >(
		allocator.malloc(BETTER_JSON_CHUNK_SIZE)
		);
}

template< Allocator TAllocator >
MemoryPool< TAllocator >::~MemoryPool() noexcept
{
	if(fileBuffer)
		TAllocator::free(fileBuffer.value());

	ChunkHeader* temp;
	while((temp = first) != nullptr)
	{
		first = first->next;
		TAllocator::free(temp);
	}
}

template< Allocator TAllocator >
MemoryPool< TAllocator >::MemoryPool(MemoryPool&& mp)
{
	this->first = mp.first;
	this->last = mp.last;
	this->fileBuffer = mp.fileBuffer;

	mp.first = mp.last = nullptr;
	mp.fileBuffer.reset();
}


template< Allocator TAllocator >
MemoryPool< TAllocator >& MemoryPool< TAllocator >::operator=(MemoryPool&& mp)
{
	if(this->fileBuffer)
		TAllocator::free(this->fileBuffer.value());

	ChunkHeader* temp;
	while((temp = this->first) != nullptr)
	{
		this->first = this->first->next;
		TAllocator::free(temp);
	}

	this->first = mp.first;
	this->last = mp.last;
	this->fileBuffer = mp.fileBuffer;

	mp.first = mp.last = nullptr;
	mp.fileBuffer.reset();

	return &this;
}


template< Allocator TAllocator >
void MemoryPool< TAllocator >::free(void* addr [[maybe_unused]])
{
	// Do not free on call - all chunks will be released on object destruction
}

template< Allocator TAllocator >
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

template< Allocator TAllocator >
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
