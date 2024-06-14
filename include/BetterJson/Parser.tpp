#pragma once

#include <BetterJson/Parser.hpp>
#include <cctype>

namespace json::parser
{

static void skipWhitespace(char*& buffer)
{
	while(std::isspace(*buffer))
		buffer++;
}

void parseObjectValue(Allocator auto& alloc, char*& buffer, ObjValue& objValue)
{

}

PrimVariant* parseObject(Allocator auto& alloc, char*& buffer)
{
	skipWhitespace(buffer);
	if(*buffer != '{')
		; // TODO: Throw expected object start

	PrimVariant* result{alloc.malloc(sizeof(PrimVariant))};
	PrimObject& object{result->pObject = PrimObject{
							  .id = PRIM_OBJECT_ID,
							  .capacity = 0,
							  .size = 0,
							  .elements = nullptr
					  }};

	skipWhitespace(buffer);
	if(*buffer == '}')
		return result;

	do {
		alloc.realloc(object.elements, object.capacity, ++object.capacity);
		parseObjectValue(alloc, buffer, object.elements[object.size++]);
	} while(*buffer == ',');

	if(*buffer != '}')
		; // TODO: Throw expected end of object

	return result;
}

}
