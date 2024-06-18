#pragma once

#include <BetterJson/SharedCreator.hpp>


namespace json
{

inline std::shared_ptr< Json > SharedCreator::operator()(Json& json)
{
	isMovable = false;
	json.accept(*this);
	return std::move(shared);
}

inline std::shared_ptr< Json > SharedCreator::operator()(Json&& json)
{
	isMovable = true;
	json.accept(*this);
	return std::move(shared);
}

#define SHARED_CREATOR_METHOD(type)                              \
	inline void SharedCreator::visit(type& value)                \
 	{                                                            \
    	if(isMovable)                                            \
        	shared = std::make_shared< type >(std::move(value)); \
		else                                                     \
            shared = std::make_shared< type >(value);            \
	}

SHARED_CREATOR_METHOD(Object)
SHARED_CREATOR_METHOD(Array)
SHARED_CREATOR_METHOD(String)
SHARED_CREATOR_METHOD(Float)
SHARED_CREATOR_METHOD(Int)
SHARED_CREATOR_METHOD(Bool)
SHARED_CREATOR_METHOD(Null)

#undef SHARED_CREATOR_METHOD

}//namespace json
