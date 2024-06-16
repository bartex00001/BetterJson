#pragma once

#include <BetterJson/PrimTypes.hpp>


namespace json
{

union PrimVariant
{
	PrimNull pNull{.id = PRIM_NULL_ID};
	PrimArray pArray;
	PrimObject pObject;
	PrimBool pBool;
	PrimFloat pFloat;
	PrimInt pInt;
	PrimString pString;
};

struct ObjKeyValuePair
{
	char* key{};
	PrimVariant* value;
};

} // namespace json

