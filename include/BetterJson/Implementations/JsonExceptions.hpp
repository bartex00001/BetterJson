#pragma once

#include <BetterJson/JsonExceptions.hpp>


namespace json
{

#define BAD_CAST_GET_NAME(type)                   \
	template<>                                    \
	inline std::string BadCast::getName< type >() \
	{                                             \
		return #type;                             \
	}

BAD_CAST_GET_NAME(Object)
BAD_CAST_GET_NAME(Array)
BAD_CAST_GET_NAME(String)
BAD_CAST_GET_NAME(Float)
BAD_CAST_GET_NAME(Int)
BAD_CAST_GET_NAME(Bool)
BAD_CAST_GET_NAME(Null)

#undef BAD_CAST_GET_NAME

template< JsonSubclass TJson >
BadCast BadCast::create(Json& json)
{
	auto res{BadCast()};
	res.message =
		"Cannot cast 'json::"
		+ NameIdentifier()(json)
		+ "' to 'json::"
		+ getName< TJson >()
		+ "'";

	return res;
}

inline const char* BadCast::what() const noexcept
{
	return message.c_str();
}


inline std::string NameIdentifier::operator()(Json& json)
{
	name.clear();
	json.accept(*this);
	return std::move(name);
}

inline std::string NameIdentifier::operator()(Json&& json)
{
	name.clear();
	json.accept(*this);
	return std::move(name);
}

#define NAME_IDENTIFIER_VISIT(type)                                 \
	inline void NameIdentifier::visit(type& value [[maybe_unused]]) \
	{					                                            \
		name = #type;                                               \
	}

NAME_IDENTIFIER_VISIT(Object)
NAME_IDENTIFIER_VISIT(Array)
NAME_IDENTIFIER_VISIT(String)
NAME_IDENTIFIER_VISIT(Float)
NAME_IDENTIFIER_VISIT(Int)
NAME_IDENTIFIER_VISIT(Bool)
NAME_IDENTIFIER_VISIT(Null)

#undef NAME_IDENTIFIER_VISIT

}//namespace json
