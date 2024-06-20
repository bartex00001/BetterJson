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
    String(String&& other) noexcept;
    String(std::shared_ptr< Allocator > alloc, PrimString& prim);

    std::string& value();

    void accept(class Visitor& visitor) override;
};

}//namespace json
