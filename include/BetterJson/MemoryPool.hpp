#pragma once

#include <BetterJson/Allocator.hpp>


#ifndef BETTER_JSON_CHUNK_SIZE
#define BETTER_JSON_CHUNK_SIZE 4096
#endif

#if BETTER_JSON_CHUNK_SIZE < 128
#error "BETTER_JSON_CHUNK_SIZE must be at least 128 bytes long"
#endif


namespace json
{

template< Allocator TAllocator >
class MemoryPool
{
	TAllocator allocator;

	struct ChunkHeader
	{
		std::uint32_t size{};
		std::uint32_t capacity{};
		struct ChunkHeader* next{};
	};

	ChunkHeader* first{};
	ChunkHeader* last{};
	std::uint32_t chunkCount{};

	void addChunk(std::size_t n);
	void allocateToChunk(std::size_t n);

public:
	static void free(void* addr);

	[[nodiscard("Memory allocated via malloc must be released")]]
	void* malloc(std::size_t n);

	[[nodiscard("Memory allocated via malloc must be released")]]
	void* realloc(void* addr, std::size_t oldSize, std::size_t newSize);

	std::size_t size() const;
};

}// namespace json


// Include template implementation
#include <BetterJson/MemoryPool.tpp>
