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

    template<typename TAllocator>
    Int(std::shared_ptr< TAllocator > alloc, PrimInt& prim);

    long long& value();
    long long& operator=(long long val);
    Int& operator=(const Int& other);
    Int& operator=(Int&& other) noexcept;

    operator long long&();

    void accept(class Visitor& visitor) override;
};

}//namespace json
