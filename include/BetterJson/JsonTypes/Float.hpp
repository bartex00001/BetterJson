#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

class Float : public Json
{
    long double v{};

public:
    Float() = default;

    Float(long double val)
        : v(val)
    {}

    Float(const Float& other)
        : v(other.v)
    {}

    template< Allocator TAllocator >
    Float(std::shared_ptr< TAllocator > alloc, PrimFloat& prim)
        : v(prim.value)
    {
        alloc->free(&prim);
    }

    long double& value()
    {
        return v;
    }

    long double& operator=(long double val)
    {
        return v = val;
    }

    Float& operator=(const Float& other)
    {
        v = other.v;
        return *this;
    }

    operator long double&() 
    {
        return v;
    }
};

}
