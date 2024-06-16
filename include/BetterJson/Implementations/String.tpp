#pragma once

#include <BetterJson/JsonTypes/String.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

String::String(const std::string& str)
    : std::string(str)
{}

String::String(const String& other)
    : std::string(other)
{}

template< Allocator TAllocator >
String::String(std::shared_ptr< TAllocator > alloc, PrimString& prim)
    : std::string(prim.str)
{
    if(prim.owner)
        alloc->free(prim.str);

    alloc->free(&prim);
}

std::string& String::value()
{
    return *this;
}

std::string& String::operator=(const std::string& str)
{
    return *this = str;
}

String& String::operator=(const String& other)
{
    *this = other;
    return *this;
}

String& String::operator=(const char* str)
{
    return *this = str;
}

void String::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

}