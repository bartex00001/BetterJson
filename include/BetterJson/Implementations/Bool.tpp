#pragma once

#include <BetterJson/JsonTypes/Bool.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

inline Bool::Bool(bool val)
    : v(val)
{}

inline Bool::Bool(const Bool& other)
    : v(other.v)
{}

inline Bool::Bool(Bool&& other) noexcept
    : v(other.v)
{}

template< Allocator TAllocator >
Bool::Bool(std::shared_ptr< TAllocator > alloc, PrimBool& prim)
    : v(prim.value)
{
    alloc->free(&prim);
}

inline bool& Bool::value()
{
    return v;
}

inline bool& Bool::operator=(bool val)
{
    return v = val;
}

inline Bool& Bool::operator=(const Bool& other)
{
    v = other.v;
    return *this;
}

inline Bool& Bool::operator=(Bool&& other) noexcept
{
    v = other.v;
    return *this;
}

inline Bool::operator bool&()
{
    return v;
}

inline void Bool::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

}//namespace json
