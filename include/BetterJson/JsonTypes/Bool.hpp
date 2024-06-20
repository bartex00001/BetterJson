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
    Bool(std::shared_ptr< Allocator > alloc, PrimBool& prim);
    
    bool& operator=(bool val);
    Bool& operator=(const Bool& other);
    Bool& operator=(Bool&& other) noexcept;

    bool& value();

    operator bool&();

    void accept(class Visitor& visitor) override;
};

}//namespace json
