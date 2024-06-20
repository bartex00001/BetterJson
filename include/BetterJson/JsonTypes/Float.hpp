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
    Float(Float&& other) noexcept;
    Float(std::shared_ptr< Allocator > alloc, PrimFloat& prim);

    long double& value();

    long double& operator=(long double val);
    Float& operator=(const Float& other);
    Float& operator=(Float&& other) noexcept;

    operator long double&();

    void accept(class Visitor& visitor) override;
};

}//namespace json
