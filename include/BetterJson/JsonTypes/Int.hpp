#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

class Int : public Json
{
    long long v{};

public:
    Int() = default;

    Int(long long val)
        : v(val)
    {}

    Int(const Int& other)
        : v(other.v)
    {}

    template<typename TAllocator>
    Int(std::shared_ptr< TAllocator > alloc, PrimInt& prim)
        : v(prim.value)
    {
        alloc->free(&prim);
    }

    long long& value()
    {
        return v;
    }

    long long& operator=(long long val)
    {
        return v = val;
    }

    Int& operator=(const Int& other)
    {
        v = other.v;
        return *this;
    }

    operator long long&() 
    {
        return v;
    }
};

}
