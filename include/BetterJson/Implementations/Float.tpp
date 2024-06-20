#pragma once

#include <BetterJson/JsonTypes/Float.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

inline Float::Float(long double val)
    : v(val)
{}

inline Float::Float(const Float& other)
    : v(other.v)
{}

inline Float::Float(Float&& other) noexcept
    : v(other.v)
{}

Float::Float(std::shared_ptr< Allocator > alloc, PrimFloat& prim)
    : v(prim.value)
{
    alloc->free(&prim);
}

inline long double& Float::value()
{
    return v;
}

inline long double& Float::operator=(long double val)
{
    return v = val;
}

inline Float& Float::operator=(const Float& other)
{
    v = other.v;
    return *this;
}

inline Float& Float::operator=(Float&& other) noexcept
{
    v = other.v;
    return *this;
}

inline Float::operator long double&()
{
    return v;
}

inline void Float::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

}//namespace json
