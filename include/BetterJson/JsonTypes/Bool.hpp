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
    Bool(Bool&& other) noexcept;

    template< Allocator TAllocator >
    Bool(std::shared_ptr< TAllocator > alloc, PrimBool& prim);

    bool& value();
    
    bool& operator=(bool val);
    Bool& operator=(const Bool& other);
    Bool& operator=(Bool&& other) noexcept;

    operator bool&();

    void accept(class Visitor& visitor) override;
};

}//namespace json
