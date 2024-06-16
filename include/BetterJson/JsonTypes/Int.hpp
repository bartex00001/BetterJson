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

    template<typename TAllocator>
    Int(std::shared_ptr< TAllocator > alloc, PrimInt& prim);

    long long& value();
    long long& operator=(long long val);

    Int& operator=(const Int& other);

    operator long long&();

    void accept(class Visitor& visitor);
};

}
