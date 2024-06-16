#pragma once

#include <unordered_map>

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/JsonTypes/JsonVariant.hpp>
#include <BetterJson/Prim.hpp>


namespace json
{

class Object : public Json
{
    std::unordered_map< std::string, JsonVariant > data{};

public:
    Object() = default;

    template< Allocator TAllocator >
    Object(std::shared_ptr< TAllocator > alloc,  PrimObject& prim);
    Object(const Object& other);
    Object(Object&& other);

    Object& operator=(const Object& other);
    Object& operator=(Object&& other);
    Object& operator=(const std::unordered_map< std::string, std::shared_ptr< Json > >& map);
    Json& operator[](const std::string& key);

    std::size_t size() const;

    template< typename T >
    void push_back(const std::string& key, const T& value);

    template< typename T >
    void push_back(const std::string& key, T&& value);

    void push_back(const std::string& key, const std::shared_ptr< Json >& value);

    void erase(const std::string& key);

    bool contains(const std::string& key) const;
    std::optional< std::shared_ptr< Json > > getOpt(const std::string& key);
};

}
