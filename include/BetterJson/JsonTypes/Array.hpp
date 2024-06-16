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
    Array(std::shared_ptr< TAllocator > alloc, PrimArray& prim)
    {
        data.reserve(prim.size);
        for(std::size_t i{}; i < prim.size; ++i)
            data.push_back(JsonVariant(*prim.elements[i], alloc));

        alloc->free(prim.elements);
        alloc->free(&prim);
    }

    Array(const Array& other)
        : data(other.data)
    {}

    Array(Array&& other)
        : data(std::move(other.data))
    {}

    Array& operator=(const Array& other)
    {
        data = other.data;
        return *this;
    }

    Array& operator=(Array&& other)
    {
        data = std::move(other.data);
        return *this;
    }

    Array& operator=(const std::vector< std::shared_ptr< Json > >& vec)
    {
        data.clear();
        for(auto& elem : vec)
            data.push_back(JsonVariant(elem));

        return *this;
    }

    Json& operator[](std::size_t inx)
    {
        return *data[inx].getJson();
    }

    std::size_t size() const
    {
        return data.size();
    }

    template< typename T >
    void push_back(const T& elem)
    {
        data.push_back(JsonVariant(std::make_shared< T >(elem)));
    }

    template< typename T >
    void push_back(T&& elem)
    {
        data.push_back(JsonVariant(std::make_shared< T >(std::forward<T>(elem))));
    }

    void push_back(const std::shared_ptr< Json >& elem)
    {
        data.push_back(JsonVariant(elem));
    }

    void pop_back()
    {
        data.pop_back();
    }
};

}
