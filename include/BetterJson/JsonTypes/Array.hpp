#pragma once

#include <vector>
#include <optional>
#include <memory>

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/JsonTypes/JsonVariant.hpp>


namespace json
{

class Array : public Json
{
    std::vector< JsonVariant > data{};

public:
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
};

}
