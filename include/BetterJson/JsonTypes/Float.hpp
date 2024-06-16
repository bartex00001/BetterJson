#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

class Float : public Json
{
    long double v{};

public:
    Float() = default;
    Float(long double val);
    Float(const Float& other);

    template< Allocator TAllocator >
    Float(std::shared_ptr< TAllocator > alloc, PrimFloat& prim);

    long double& value();

    long double& operator=(long double val);

    Float& operator=(const Float& other);

    operator long double&();

    void accept(class Visitor& visitor);
};

}
