#pragma once

#include <BetterJson/JsonTypes/Json.hpp>


namespace json
{

template< typename T >
T& Json::as()
{
    return dynamic_cast< T& >(*this);
}

}//namespace json
