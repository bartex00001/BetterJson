#pragma once

template<typename T>
concept Allocator = requires(T& allocator)
{
  { allocator.malloc(std::declval< size_t >()) } -> std::same_as< void* >;
  { allocator.realloc(
    std::declval< void* >(),
    std::declval< size_t >(),
    std::declval< size_t >())
  } -> std::same_as< void* >;
  { T::free() };
};
