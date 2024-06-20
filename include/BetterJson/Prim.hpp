#pragma once

#include <BetterJson/PrimTypes.hpp>


namespace json
{

union PrimVariant
{
	PrimNull pNull{.id = PRIM_NULL_ID};
	PrimObject pObject;
	PrimArray pArray;
	PrimString pString;
	PrimFloat pFloat;
	PrimInt pInt;
	PrimBool pBool;
};

struct ObjKeyValuePair
{
	char* key{};
	PrimVariant* value{};
};

} // namespace json
