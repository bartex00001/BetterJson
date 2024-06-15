#pragma once

#include <cctype>

#include <BetterJson/Exceptions.hpp>
#include <BetterJson/Parser.hpp>
#include <bits/socket.h>


namespace json
{

template< Allocator TAllocator >
void Parser< TAllocator >::skipWhitespace()
{
	while(std::isspace(file.get().peek()))
		file.get().get();
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseString(char*& str)
{
	skipWhitespace();
	if(!file.get().consume('"'))
		throw SyntaxError(file);

	std::size_t strLen{};


	bool neutralized{};
	char curr{file.get().get()};
	while(curr != '"' || neutralized)
	{
		neutralized = file.get().peek() == '\\';
		alloc.get().realloc(str, strLen, strLen+1);
		str[strLen++] = curr;
	}

	alloc.get().realloc(str, strLen, strLen+1);
	str[strLen] = '\0';
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseObjectValue(ObjKeyValuePair& objKeyVal)
{
	parseString(objKeyVal.key);
	parseAnyPrim(objKeyVal.value);
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseNumber(PrimVariant& primVariant)
{
	constexpr std::size_t buffSize{64};
	char buffor[buffSize];
	std::size_t inx{};
	if(file.get().consume('-'))
	{
		buffor[inx++] = '-';
		if(!isdigit(file.get().peek()))
			throw SyntaxError(file);
	}

	bool isFloat{};
	char curr{file.get().get()};
	while(isdigit(curr) || curr == 'e' || curr == 'E' || curr == '.')
	{
		isFloat |= curr == 'e' || curr == 'E' || curr == '.';
		buffor[inx++] = curr;
		curr = file.get().get();
		if(inx >= buffSize-1)
			throw SyntaxError(file);
	}
	buffor[inx] = '\0';

	if(isFloat)
		parseFloat(primVariant.pFloat, buffor, buffor + inx);
	else
		parseInt(primVariant.pInt, buffor, buffor + inx);
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseAnyPrim(PrimVariant& primVariant)
{
	skipWhitespace();

	if(isdigit(file.get().peek())) // No good way for encoding this in a switch
	{
		parseNumber(primVariant);
		return;
	}

	switch(file.get().peek())
	{
	case '{':
		parseObject(primVariant.pObject);
		break;
	case '[':
		parseArray(primVariant.pArray);
		break;
	case '"':
		parseString(primVariant.pString);
		break;
	case 't':
	case 'f':
		parseBool(primVariant.pBool);
		break;
	case 'n':
		parseNull(primVariant.pNull);
		break;
	case '-':
		parseNumber(primVariant);
		break;
	default:
		throw SyntaxError(file);
	}
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseObject(PrimObject& obj)
{
	skipWhitespace(file);
	if(!file.get().consume('{'))
		throw SyntaxError(file);

	obj = PrimObject{
		.id = PRIM_OBJECT_ID,
		.capacity = 0,
		.size = 0,
		.elements = nullptr
	};

	skipWhitespace();
	if(file.get().consume('}'))
		return;

	do
	{
		alloc.realloc(obj.elements, obj.capacity, obj.capacity += sizeof(ObjKeyValuePair));
		parseObjectValue(obj.elements[obj.size]);
		obj.size += sizeof(ObjKeyValuePair);
	} while(file.get().consume(','));

	if(!file.get().consume('}'))
		throw SyntaxError(file);
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseArray(PrimArray& arr)
{
	skipWhitespace();
	if(!file.get().consume('['))
		throw SyntaxError(file);

	arr = PrimArray{
		.id = PRIM_ARRAY_ID,
		.size = 0,
		.capacity = 0,
		.elements = nullptr
	};

	skipWhitespace();
	if(file.get().consume(']'))
		return;

	do
	{
		alloc.realloc(arr.elements, arr.capacity, arr.capacity += sizeof(ObjKeyValuePair));
		parseObjectValue(arr.elements[arr.size]);
		arr.size += sizeof(ObjKeyValuePair);
	} while(file.get().consume(','));

	if(!file.get().consume(']'))
		throw SyntaxError(file);
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseString(PrimString& str)
{
	str = PrimString{
		.id = PRIM_STRING_ID,
		.owner = true
	};

	parseString(str.str);
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseInt(PrimInt& i, char buffor[], const char* end)
{
	char* readEnd;
	i = PrimInt{
		.id = PRIM_INT_ID,
		.value = std::strtoll(buffor, &readEnd, 10)
	};

	if(readEnd != end)
		throw SyntaxError(file);
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseFloat(PrimFloat& f, char buffor[], const char* end)
{
	char* readEnd;
	f = PrimFloat{
		.id = PRIM_FLOAT_ID,
		.value = std::strtold(buffor, &readEnd)
	};

	if(readEnd != end)
		throw SyntaxError(file);
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseBool(PrimBool& b)
{
	b.id = PRIM_BOOL_ID;

	if(file.get().consume('t'))
	{
		bool isTrue{file.get().consume('r')
			&& file.get().consume('u')
			&& file.get().consume('e')};

		if(!isTrue)
			throw SyntaxError(file);

		b.value = true;
	}
	else if(file.get().consume('f'))
	{
		bool isFalse{file.get().consume('a')
			&& file.get().consume('l')
			&& file.get().consume('s')
			&& file.get().consume('e')};

		if(!isFalse)
			throw SyntaxError(file);

		b.value = false;
	}
	else
		throw SyntaxError(file);
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseNull(PrimNull& null)
{
	bool isNull{file.get().consume('n')
		&& file.get().consume('u')
		&& file.get().consume('l')
		&& file.get().consume('l')};

	if(!isNull)
		throw SyntaxError(file);

	null.id = PRIM_NULL_ID;
}


template< Allocator TAllocator >
Parser< TAllocator >::Parser(TAllocator& alloc, File& file)
	: alloc(alloc),
      file(file)
{
}

}
