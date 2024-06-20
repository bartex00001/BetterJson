#pragma once

#include <unordered_map>

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/JsonTypes/JsonVariant.hpp>
#include <BetterJson/Prim.hpp>


namespace json
{

class ObjectIterator;

class Object : public Json
{
    std::unordered_map< std::string, JsonVariant > data{};

public:
    using iterator = ObjectIterator;
    friend class ObjectIterator;

    Object() = default;
    Object(const Object& other);
    Object(Object&& other) noexcept;
    Object(std::shared_ptr< Allocator > alloc,  PrimObject& prim);


    Object& operator=(const Object& other);
    Object& operator=(Object&& other) noexcept;
    Object& operator=(const std::unordered_map< std::string, std::shared_ptr< Json > >& map);

    Json& operator[](const std::string& key);
    std::shared_ptr< Json >& getOwner(const std::string& key);

    void accept(class Visitor& visitor) override;

    std::size_t size() const;

    void emplace(const std::string& key, Json& value);
    void emplace(const std::string& key, Json&& value);
	void emplace(const std::string& key, const std::shared_ptr< Json >& value);

    void erase(const std::string& key);

    bool contains(const std::string& key) const;
	std::optional< std::reference_wrapper< Json > > getOpt(const std::string& key);

    void clear();

    iterator begin();
    iterator end();
};


class ObjectIterator
{
    Object& obj;
    std::unordered_map< std::string, JsonVariant >::iterator it;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair< std::string, Json& >;
    using difference_type = std::ptrdiff_t;
    using pointer = Json*;
    using reference = std::pair< std::string, Json& >;

    ObjectIterator(Object& obj, std::unordered_map< std::string, JsonVariant >::iterator it);

    reference operator*();
    pointer operator->();

    ObjectIterator& operator++();
    ObjectIterator operator++(int);

    friend bool operator!=(const ObjectIterator& a, const ObjectIterator& b);
    friend bool operator==(const ObjectIterator& a, const ObjectIterator& b);
};

}//namespace json
