#pragma once

#include <cstdint>


namespace json
{

using TypeId = std::uint8_t;
constexpr TypeId PRIM_NULL_ID{0x1};
constexpr TypeId PRIM_ARRAY_ID{0x2};
constexpr TypeId PRIM_OBJECT_ID{0x3};
constexpr TypeId PRIM_BOOL_ID{0x4};
constexpr TypeId PRIM_FLOAT_ID{0x5};
constexpr TypeId PRIM_INT_ID{0x6};
constexpr TypeId PRIM_STRING_ID{0x7};


struct PrimNull
{
	TypeId id;
};

struct PrimArray
{
	TypeId id;
	std::uint32_t size;
	std::uint32_t capacity;
	union PrimVariant** elements;
};

struct PrimObject
{
	TypeId id;
	std::uint32_t size;
	std::uint32_t capacity;
	struct ObjKeyValuePair** elements;
};

struct PrimBool
{
	TypeId id;
	bool value;
};

struct PrimFloat
{
	TypeId id;
	long double value;
};

struct PrimInt
{
	TypeId id;
	long long value;
};

struct PrimString
{
	TypeId id;
	bool owner;
	char* str;
};

}// namespace json
