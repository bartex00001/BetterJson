#pragma once

#include <BetterJson/JsonTypes/Array.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/SharedCreator.hpp>
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

inline Array::Array(const Array& other)
    : data(other.data)
{}

inline Array::Array(Array&& other) noexcept
    : data(std::move(other.data))
{}

inline Array& Array::operator=(const Array& other)
{
    data = other.data;
    return *this;
}

inline Array& Array::operator=(Array&& other) noexcept
{
    data = std::move(other.data);
    return *this;
}

inline Array& Array::operator=(const std::vector< std::shared_ptr< Json > >& vec)
{
    data.clear();
    for(const auto& elem : vec)
        data.emplace_back(elem);

    return *this;
}

inline Json& Array::operator[](std::size_t inx)
{
    return *data[inx].getJson();
}

inline std::shared_ptr< Json >& Array::getOwner(std::size_t inx)
{
    return data[inx].getRawJson();
}

inline std::size_t Array::size() const
{
    return data.size();
}

void Array::push_back(Json& elem)
{
    data.emplace_back(SharedCreator()(elem));
}

void Array::push_back(Json&& elem)
{
    data.emplace_back(SharedCreator()(elem));
}

inline void Array::push_back(const std::shared_ptr< Json >& elem)
{
    data.emplace_back(elem);
}

inline void Array::pop_back()
{
    data.pop_back();
}

inline void Array::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

inline Array::iterator Array::begin()
{
    return {*this};
}

inline Array::iterator Array::end()
{
    return {*this, data.size()};
}


inline ArrayIterator::ArrayIterator(Array& arr, std::size_t inx)
    : arr(arr), inx(inx)
{}

inline Json& ArrayIterator::operator*() const
{
    return *arr.data[inx].getJson();
}

inline Json* ArrayIterator::operator->() const
{
    return arr.data[inx].getJson().get();
}

inline ArrayIterator& ArrayIterator::operator++()
{
    ++inx;
    return *this;
}

inline ArrayIterator ArrayIterator::operator++(int)
{
    ArrayIterator temp(*this);
    ++inx;
    return temp;
}

inline bool operator==(const ArrayIterator& a, const ArrayIterator& b)
{
    return a.inx == b.inx;
}

inline bool operator!=(const ArrayIterator& a, const ArrayIterator& b)
{
    return a.inx != b.inx;
}

}//namespace json
