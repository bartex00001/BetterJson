#pragma once

#include <BetterJson/JsonTypes/Array.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

template< Allocator TAllocator >
Array::Array(std::shared_ptr< TAllocator > alloc, PrimArray& prim)
{
    data.reserve(prim.size);
    for(std::size_t i{}; i < prim.size; ++i)
        data.push_back(JsonVariant(*prim.elements[i], alloc));

    alloc->free(prim.elements);
    alloc->free(&prim);
}

Array::Array(const Array& other)
    : data(other.data)
{}

Array::Array(Array&& other)
    : data(std::move(other.data))
{}

Array& Array::operator=(const Array& other)
{
    data = other.data;
    return *this;
}

Array& Array::operator=(Array&& other)
{
    data = std::move(other.data);
    return *this;
}

Array& Array::operator=(const std::vector< std::shared_ptr< Json > >& vec)
{
    data.clear();
    for(auto& elem : vec)
        data.push_back(JsonVariant(elem));

    return *this;
}

Json& Array::operator[](std::size_t inx)
{
    return *data[inx].getJson();
}

std::size_t Array::size() const
{
    return data.size();
}

template< typename T >
void Array::push_back(const T& elem)
{
    data.push_back(JsonVariant(std::make_shared< T >(elem)));
}

template< typename T >
void Array::push_back(T&& elem)
{
    data.push_back(JsonVariant(std::make_shared< T >(std::forward<T>(elem))));
}

void Array::push_back(const std::shared_ptr< Json >& elem)
{
    data.push_back(JsonVariant(elem));
}

void Array::pop_back()
{
    data.pop_back();
}

void Array::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

Array::iterator Array::begin()
{
    return ArrayIterator(*this);
}

Array::iterator Array::end()
{
    return ArrayIterator(*this, data.size());
}


ArrayIterator::ArrayIterator(Array& arr, std::size_t inx)
    : arr(arr), inx(inx)
{}

Json& ArrayIterator::operator*()
{
    return *arr.data[inx].getJson();
}

Json* ArrayIterator::operator->()
{
    return arr.data[inx].getJson().get();
}

ArrayIterator& ArrayIterator::operator++()
{
    ++inx;
    return *this;
}

ArrayIterator ArrayIterator::operator++(int)
{
    ArrayIterator temp(*this);
    ++inx;
    return temp;
}

bool operator==(const ArrayIterator& a, const ArrayIterator& b)
{
    return a.inx == b.inx;
}

bool operator!=(const ArrayIterator& a, const ArrayIterator& b)
{
    return a.inx != b.inx;
}

}
