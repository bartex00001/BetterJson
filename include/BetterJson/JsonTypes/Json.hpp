#pragma once

#include <memory>

#include <BetterJson/MemoryPool.hpp>
#include <BetterJson/CStdAllocator.hpp>
// #include <BetterJson/Visitor.hpp>

#define DEFAULT_ALLOCATOR MemoryPool< CStdAllocator >


namespace json
{

class Json
{
    Json(const Json& other) = delete;
    Json(Json&& other) = delete;
    Json& operator=(const Json& other) = delete;
    Json& operator=(Json&& other) = delete;

protected:
	Json() = default;

public:
	template< typename T >
	T& castTo();

	template< typename T >
	T& as();

	template< typename T >
	auto operator=(T& value) -> T&;

	Json& operator[](const std::string& key);

    // template< typename T >
    // operator T&();

    // virtual void accept(class Visitor& visitor) = 0;

    virtual ~Json() = default;
};

}// namespace json

