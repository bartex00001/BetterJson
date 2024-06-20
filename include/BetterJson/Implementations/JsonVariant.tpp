#pragma once

#include <BetterJson/JsonTypes/JsonVariant.hpp>

#include <BetterJson/JsonTypes/Array.hpp>
#include <BetterJson/JsonTypes/Bool.hpp>
#include <BetterJson/JsonTypes/Float.hpp>
#include <BetterJson/JsonTypes/Int.hpp>
#include <BetterJson/JsonTypes/Null.hpp>
#include <BetterJson/JsonTypes/Object.hpp>
#include <BetterJson/JsonTypes/String.hpp>


namespace json
{

inline JsonVariant::JsonVariant(PrimVariant& primVariant, std::shared_ptr< Allocator > alloc)
	: json(primVariant),
      allocator(alloc)
{}

inline JsonVariant::JsonVariant(std::shared_ptr< Json > jsonType)
	: json(jsonType)
{}

inline std::shared_ptr< Json >& JsonVariant::getInsideJsonRef()
{
	if(std::holds_alternative< std::shared_ptr< Json > >(json))
		return std::get< std::shared_ptr< Json > >(json);

	PrimVariant& prim{std::get< std::reference_wrapper< PrimVariant > >(json).get()};
	switch(prim.pNull.id)
	{
	case PRIM_NULL_ID:
		json = std::make_shared< Null >(allocator.value(), prim.pNull);
		break;
	case PRIM_ARRAY_ID:
		json = std::make_shared< Array >(allocator.value(), prim.pArray);
		break;
	case PRIM_OBJECT_ID:
		json = std::make_shared< Object >(allocator.value(), prim.pObject);
		break;
	case PRIM_BOOL_ID:
		json = std::make_shared< Bool >(allocator.value(), prim.pBool);
		break;
	case PRIM_FLOAT_ID:
		json = std::make_shared< Float >(allocator.value(), prim.pFloat);
		break;
	case PRIM_INT_ID:
		json = std::make_shared< Int >(allocator.value(), prim.pInt);
		break;
	case PRIM_STRING_ID:
		json = std::make_shared< String >(allocator.value(), prim.pString);
		break;
	default:
		throw std::runtime_error("Unknown prim json type");
	}

	allocator.reset();
	return std::get< std::shared_ptr< Json > >(json);
}

inline std::shared_ptr< Json > JsonVariant::getJson()
{
	return getInsideJsonRef();
}

}//namespace json
