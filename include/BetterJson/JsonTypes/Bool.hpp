#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

class Bool : public Json
{
    bool v{};

public:
    Bool() = default;

    Bool(bool val)
        : v(val)
    {}

    Bool(const Bool& other)
        : v(other.v)
    {}

    template< Allocator TAllocator >
    Bool(std::shared_ptr< TAllocator > alloc, PrimBool& prim)
        : v(prim.value)
    {
        // alloc->free(&prim);
    }

    bool& value()
    {
        return v;
    }

    bool& operator=(bool val)
    {
        return v = val;
    }

    Bool& operator=(const Bool& other)
    {
        v = other.v;
        return *this;
    }

    operator bool&()
    {
        return v;
    }
};

}
