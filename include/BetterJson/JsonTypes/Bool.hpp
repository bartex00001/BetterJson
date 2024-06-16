#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

class Bool : public Json
{
    bool v{};

public:
    Bool() = default;
    Bool(bool val);
    Bool(const Bool& other);

    template< Allocator TAllocator >
    Bool(std::shared_ptr< TAllocator > alloc, PrimBool& prim);

    bool& value();
    
    bool& operator=(bool val);
    Bool& operator=(const Bool& other);

    operator bool&();

    void accept(class Visitor& visitor);
};

}
