#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

class String : public Json, public std::string
{
public:
    String() = default;

    String(const std::string& str)
        : std::string(str)
    {}

    String(const String& other)
        : std::string(other)
    {}

    template< Allocator TAllocator >
    String(std::shared_ptr< TAllocator > alloc, PrimString& prim)
        : std::string(prim.str)
    {
        if(prim.owner)
            alloc->free(prim.str);

        alloc->free(&prim);
    }

    std::string& value();

    std::string& operator=(const std::string& str)
    {
        return *this = str;
    }

    String& operator=(const String& other)
    {
        *this = other;
        return *this;
    }

    String& operator=(const char* str)
    {
        return *this = str;
    }
};

}
