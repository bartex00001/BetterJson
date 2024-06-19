#pragma once

#include <BetterJson/JsonBase.hpp>

namespace json
{

inline JSON_BASE::JSON_BASE(Json& json)
    : json(json)
{}

template< typename T >
    requires std::is_integral_v< T >
auto JSON_BASE::retrieve(Json& j) -> T
{
    return static_cast< T >(j.as< Int >());
}

template< typename T >
    requires std::is_floating_point_v< T >
auto JSON_BASE::retrieve(Json& j) -> T
{
    return static_cast< T >(j.as< Float >());
}

template< typename T >
    requires std::is_same_v< T, bool >
auto JSON_BASE::retrieve(Json& j) -> T
{
    return j.as< Bool >();
}

template< typename T >
    requires std::is_base_of_v< std::string, T >
auto JSON_BASE::retrieve(Json& j) -> T
{
    return j.as< String >();
}

}//namespace json
