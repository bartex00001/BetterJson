#pragma once

#include <BetterJson/JsonTypes/String.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

inline String::String(const std::string& str)
    : std::string(str)
{}

inline String::String(const String& other)
    : std::string(other)
{}

inline String::String(String&& other) noexcept
    : std::string(std::move(other))
{}

template< Allocator TAllocator >
String::String(std::shared_ptr< TAllocator > alloc, PrimString& prim)
    : std::string(prim.str)
{
    if(prim.owner)
        alloc->free(prim.str);

    alloc->free(&prim);
}

inline std::string& String::value()
{
    return *this;
}


inline void String::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

}//namespace json
