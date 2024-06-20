#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

class Int : public Json
{
    long long v{};

public:
    Int() = default;
    Int(long long val);
    Int(const Int& other);
    Int(Int&& other) noexcept;
    Int(std::shared_ptr< Allocator > alloc, PrimInt& prim);

    long long& operator=(long long val);
    Int& operator=(const Int& other);
    Int& operator=(Int&& other) noexcept;

    long long& value();

    operator long long&();

    void accept(class Visitor& visitor) override;
};

}//namespace json
