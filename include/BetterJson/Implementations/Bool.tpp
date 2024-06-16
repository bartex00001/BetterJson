#pragma once

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/Prim.hpp>


namespace json
{

Bool::Bool(bool val)
    : v(val)
{}

Bool::Bool(const Bool& other)
    : v(other.v)
{}

template< Allocator TAllocator >
Bool::Bool(std::shared_ptr< TAllocator > alloc, PrimBool& prim)
    : v(prim.value)
{
    alloc->free(&prim);
}

bool& Bool::value()
{
    return v;
}

bool& Bool::operator=(bool val)
{
    return v = val;
}

Bool& Bool::operator=(const Bool& other)
{
    v = other.v;
    return *this;
}

Bool::operator bool&()
{
    return v;
}

}