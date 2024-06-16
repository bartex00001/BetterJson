#pragma once

#include <memory>

#include <BetterJson/File.hpp>
#include <BetterJson/MemoryPool.hpp>
#include <BetterJson/CStdAllocator.hpp>

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

    virtual ~Json() = default;
};


inline std::shared_ptr< Json > parse(File& file);
inline std::shared_ptr< Json > parse(File&& file);

}// namespace json

#include <BetterJson/Implementations/Json.tpp>
