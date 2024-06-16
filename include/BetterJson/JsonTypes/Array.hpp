#pragma once

#include <vector>
#include <optional>
#include <memory>

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/JsonTypes/JsonVariant.hpp>


namespace json
{

class ArrayIterator;

class Array : public Json
{
    std::vector< JsonVariant > data{};

public:
    using iterator = ArrayIterator;
    friend class ArrayIterator;

    Array() = default;

    template< Allocator TAllocator >
    Array(std::shared_ptr< TAllocator > alloc, PrimArray& prim);
    Array(const Array& other);
    Array(Array&& other);

    Array& operator=(const Array& other);
    Array& operator=(Array&& other);
    Array& operator=(const std::vector< std::shared_ptr< Json > >& vec);

    Json& operator[](std::size_t inx);

    std::size_t size() const;

    template< typename T >
    void push_back(const T& elem);

    template< typename T >
    void push_back(T&& elem);

    void push_back(const std::shared_ptr< Json >& elem);

    void pop_back();

    void accept(class Visitor& visitor);

    iterator begin();
    iterator end();
};


class ArrayIterator
{
    Array& arr;
    std::size_t inx{};

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Json&;
    using difference_type = std::ptrdiff_t;
    using pointer = Json*;
    using reference = Json&;

    ArrayIterator(Array& arr, std::size_t inx = 0);

    reference operator*();
    pointer operator->();

    ArrayIterator& operator++();
    ArrayIterator operator++(int);

    friend bool operator!=(const ArrayIterator& a, const ArrayIterator& b);
    friend bool operator==(const ArrayIterator& a, const ArrayIterator& b);
};

}
