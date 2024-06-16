#pragma once

#include <BetterJson/JsonTypes/Float.hpp>
#include <BetterJson/Prim.hpp>


namespace json
{

Float::Float(long double val)
    : v(val)
{}

Float::Float(const Float& other)
    : v(other.v)
{}

template< Allocator TAllocator >
Float::Float(std::shared_ptr< TAllocator > alloc, PrimFloat& prim)
    : v(prim.value)
{
    alloc->free(&prim);
}

long double& Float::value()
{
    return v;
}

long double& Float::operator=(long double val)
{
    return v = val;
}

Float& Float::operator=(const Float& other)
{
    v = other.v;
    return *this;
}

Float::operator long double&() 
{
    return v;
}

}
