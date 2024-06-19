#pragma once

#include <BetterJson/JsonTypes/Object.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>
#include <BetterJson/SharedCreator.hpp>


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

inline Object::Object(const Object& other)
    : data(other.data)
{}

inline Object::Object(Object&& other) noexcept
    : data(std::move(other.data))
{}

inline Object& Object::operator=(const Object& other)
{
    data = other.data;
    return *this;
}

inline Object& Object::operator=(Object&& other) noexcept
{
    data = std::move(other.data);
    return *this;
}

inline Object& Object::operator=(const std::unordered_map< std::string, std::shared_ptr< Json > >& map)
{
    data.clear();
    for(const auto& [key, value] : map)
        data.emplace(key, JsonVariant(value));

    return *this;
}

inline Json& Object::operator[](const std::string& key)
{
    if(!contains(key))
        emplace(key, json::Null());

    return *data[key].getJson();
}

inline std::shared_ptr< Json >& Object::getOwner(const std::string& key)
{
    if(!contains(key))
        emplace(key, json::Null());

    return data[key].getRawJson();
}

inline std::size_t Object::size() const
{
    return data.size();
}

inline void Object::emplace(const std::string& key, Json& value)
{
	data.emplace(key, SharedCreator()(value));
}

inline void Object::emplace(const std::string& key, Json&& value)
{
	data.emplace(key, SharedCreator()(value));
}

inline void Object::emplace(const std::string& key, const std::shared_ptr< Json >& value)
{
	data.emplace(key, JsonVariant(value));
}

inline void Object::erase(const std::string& key)
{
    data.erase(key);
}

inline bool Object::contains(const std::string& key) const
{
    return data.contains(key);
}

inline std::optional< std::reference_wrapper< Json > > Object::getOpt(const std::string& key)
{
    if(!contains(key))
        return std::nullopt;

    return *data[key].getJson();
}

inline void Object::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

inline void Object::clear()
{
	data.clear();
}


inline Object::iterator Object::begin()
{
    return {*this, data.begin()};
}

inline Object::iterator Object::end()
{
    return {*this, data.end()};
}


inline ObjectIterator::ObjectIterator(Object& obj, std::unordered_map< std::string, JsonVariant >::iterator it)
    : obj(obj), it(it)
{}

inline std::pair< std::string, Json& > ObjectIterator::operator*()
{
    return {it->first, *it->second.getJson()};
}

inline Json* ObjectIterator::operator->()
{
    return it->second.getJson().get();
}

inline ObjectIterator& ObjectIterator::operator++()
{
    ++it;
    return *this;
}

inline ObjectIterator ObjectIterator::operator++(int)
{
    ObjectIterator temp(*this);
    ++it;
    return temp;
}

inline bool operator==(const ObjectIterator& a, const ObjectIterator& b)
{
    return a.it == b.it;
}

inline bool operator!=(const ObjectIterator& a, const ObjectIterator& b)
{
    return a.it != b.it;
}

}//namespace json
