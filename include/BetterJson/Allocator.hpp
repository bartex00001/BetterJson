#pragma once

#include <utility>

template< typename T >
concept Allocator = requires(T& allocator)
{
  { allocator.malloc(std::declval< std::size_t >()) } -> std::same_as< void* >;
  { allocator.realloc(
    std::declval< void* >(),
    std::declval< std::size_t >(),
    std::declval< std::size_t >())
  } -> std::same_as< void* >;
  { T::free(std::declval< void* >()) };
};
