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
	uint32_t size;
	uint32_t capacity;
	union PrimVariant* elements;
};

struct PrimObject
{
	TypeId id;
	uint32_t capacity;
	uint32_t size;
	struct ObjValue* elements;
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
	TypeId id{};
	__int128_t value{};
};

struct PrimString
{
	TypeId id;
	bool owner;
	char* str;
};

}// namespace json