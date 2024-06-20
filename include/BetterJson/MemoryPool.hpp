#pragma once

#include <cstdint>

#include <BetterJson/Allocator.hpp>


namespace json
{

template< typename TAllocator >
	requires std::is_base_of_v< Allocator, TAllocator >
class MemoryPool : public Allocator
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

	MemoryPool(MemoryPool&& mp) noexcept;
	MemoryPool& operator=(MemoryPool&& mp) noexcept;

	[[nodiscard("Memory allocated via malloc must be released")]]
	void* malloc(std::size_t n) override;

	[[nodiscard("Memory allocated via malloc must be released")]]
	void* realloc(void* addr, std::size_t oldSize, std::size_t newSize) override;

	void free(void* addr) noexcept override;
};

}// namespace json
