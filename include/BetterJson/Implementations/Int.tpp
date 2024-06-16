#pragma once

#include <BetterJson/JsonTypes/Int.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

Int::Int(long long val)
    : v(val)
{}

Int::Int(const Int& other)
    : v(other.v)
{}

template<typename TAllocator>
Int::Int(std::shared_ptr< TAllocator > alloc, PrimInt& prim)
    : v(prim.value)
{
    alloc->free(&prim);
}

long long& Int::value()
{
    return v;
}

long long& Int::operator=(long long val)
{
    return v = val;
}

Int& Int::operator=(const Int& other)
{
    v = other.v;
    return *this;
}

Int::operator long long&() 
{
    return v;
}

void Int::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

}
