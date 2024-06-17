#pragma once

#include <BetterJson/JsonTypes/Int.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

inline Int::Int(long long val)
    : v(val)
{}

inline Int::Int(const Int& other)
    : v(other.v)
{}

inline Int::Int(Int&& other) noexcept
    : v(other.v)
{}

template<typename TAllocator>
Int::Int(std::shared_ptr< TAllocator > alloc, PrimInt& prim)
    : v(prim.value)
{
    alloc->free(&prim);
}

inline long long& Int::value()
{
    return v;
}

inline long long& Int::operator=(long long val)
{
    return v = val;
}

inline Int& Int::operator=(const Int& other)
{
    v = other.v;
    return *this;
}

inline Int& Int::operator=(Int&& other) noexcept
{
    v = other.v;
    return *this;
}

inline Int::operator long long&()
{
    return v;
}

inline void Int::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

}//namespace json
