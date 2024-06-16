#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

class Null : public Json
{
public:
    Null() = default;

    template< Allocator TAllocator >
    Null(std::shared_ptr< TAllocator > alloc, PrimNull& pNull);

    void accept(class Visitor& visitor);
};

}
