#pragma once

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/JsonExceptions.hpp>

namespace json
{

template< typename T >
	requires std::is_base_of_v< Json, T >
auto Json::as() -> T&
{
	try
	{
		return dynamic_cast< T& >(*this);
	}
	catch(const std::bad_cast& badCast [[maybe_unused]])
	{
		throw BadCast::create< T >(*this);
	}
}

template< typename T >
	requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)
auto Json::operator=(T& other) -> T&
{
	return this->as< T >() = other;
}

template< typename T >
	requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)
auto Json::operator=(T&& other) -> T&
{
	return this->as< T >() = other;
}


}//namespace json
