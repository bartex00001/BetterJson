#pragma once

#include <BetterJson/JsonTypes/Object.hpp>
#include <BetterJson/Prim.hpp>


namespace json
{

template< Allocator TAllocator >
Object::Object(std::shared_ptr< TAllocator > alloc,  PrimObject& prim)
{
    data.reserve(prim.size);
    for(std::size_t i{}; i < prim.size; ++i)
    {
        data[std::string(prim.elements[i]->key)] = JsonVariant(*prim.elements[i]->value, alloc);
        alloc->free(prim.elements[i]->key);
        alloc->free(prim.elements[i]);
    }

    alloc->free(prim.elements);
    alloc->free(&prim);
}

Object::Object(const Object& other)
    : data(other.data)
{}

Object::Object(Object&& other)
    : data(std::move(other.data))
{}

Object& Object::operator=(const Object& other)
{
    data = other.data;
    return *this;
}

Object& Object::operator=(Object&& other)
{
    data = std::move(other.data);
    return *this;
}

Object& Object::operator=(const std::unordered_map< std::string, std::shared_ptr< Json > >& map)
{
    data.clear();
    for(auto& [key, value] : map)
        data.emplace(key, JsonVariant(value));

    return *this;
}

Json& Object::operator[](const std::string& key)
{
    return *data[key].getJson();
}

std::size_t Object::size() const
{
    return data.size();
}

template< typename T >
void Object::push_back(const std::string& key, const T& value)
{
    data.emplace(key, JsonVariant(std::make_shared< T >(value)));
}

template< typename T >
void Object::push_back(const std::string& key, T&& value)
{
    data.emplace(key, JsonVariant(std::make_shared< T >(std::forward<T>(value))));
}

void Object::push_back(const std::string& key, const std::shared_ptr< Json >& value)
{
    data.emplace(key, JsonVariant(value));
}

void Object::erase(const std::string& key)
{
    data.erase(key);
}

bool Object::contains(const std::string& key) const
{
    return data.contains(key);
}

std::optional< std::shared_ptr< Json > > Object::getOpt(const std::string& key)
{
    if(!contains(key))
        return std::nullopt;

    return data[key].getJson();
}

}