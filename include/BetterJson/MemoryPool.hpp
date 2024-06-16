#pragma once

#include <optional>

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
		ChunkHeader* next{};
	};

	ChunkHeader* first{};
	ChunkHeader* last{};

	void addChunk(std::size_t n);
	void* allocate(std::size_t n);

	bool canFitAlloc(std::size_t n) const;
	bool isLastElement(const void* addr, std::size_t elementSize) const;
	static constexpr bool largerThanChunk(std::size_t n);

public:
	MemoryPool();
	~MemoryPool() noexcept;

	MemoryPool(const MemoryPool& mp) = delete;
	MemoryPool operator=(const MemoryPool& mp) = delete;

	MemoryPool(MemoryPool&& mp);
	MemoryPool& operator=(MemoryPool&& mp);

	static void free(auto* addr);

	[[nodiscard("Memory allocated via malloc must be released")]]
	void* malloc(std::size_t n);

	[[nodiscard("Memory allocated via malloc must be released")]]
	auto realloc(auto* addr, std::size_t oldSize, std::size_t newSize) -> decltype(addr);
};

}// namespace json


// Include template implementation
#include <BetterJson/Implementations/MemoryPool.tpp>
