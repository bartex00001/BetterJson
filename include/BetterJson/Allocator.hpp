#pragma once

#include <utility>


template< typename T >
concept Allocator = requires(T& allocator)
{
	{ T() };
	{ allocator.malloc(std::declval< std::size_t >()) } -> std::same_as< void* >;
	{ allocator.realloc(
		std::declval< void* >(),
		std::declval< std::size_t >(),
		std::declval< std::size_t >())
	} -> std::same_as< void* >;
	{ T::free(std::declval< void* >()) };

	{ T(std::move(std::declval< T >())) };
	{ std::declval< T >() = std::move(std::declval< T >()) } -> std::same_as< T& >;
};


#include <BetterJson/MemoryPool.hpp>
#include <BetterJson/CStdAllocator.hpp>

namespace json
{

using DefaultAllocator = MemoryPool< CStdAllocator >;

static_assert(Allocator< CStdAllocator >);
static_assert(Allocator< MemoryPool< CStdAllocator > >);

}//namespace json
