#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

class String : public Json, public std::string
{
public:
    String() = default;
    String(const std::string& str);
    String(const String& other);

    template< Allocator TAllocator >
    String(std::shared_ptr< TAllocator > alloc, PrimString& prim);

    std::string& value();

    std::string& operator=(const std::string& str);
    String& operator=(const String& other);
    String& operator=(const char* str);

    void accept(class Visitor& visitor);
};

}
