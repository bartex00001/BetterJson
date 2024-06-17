#pragma once

#include <cctype>
#include <ranges>

#include <BetterJson/Exceptions.hpp>
#include <BetterJson/JsonTypes/JsonVariant.hpp>
#include <BetterJson/Parser.hpp>
#include <BetterJson/PrimTypes.hpp>


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
	std::size_t strCap{};

	bool neutralized{};
	char curr{file.get().peek()};
	while(curr != '"' || neutralized)
	{
		if(strLen == strCap)
        {
			str = alloc.get().realloc(str, strCap, strCap + BETTER_JSON_ARRAY_DEFAULT_CAPACITY);
            strCap += BETTER_JSON_ARRAY_DEFAULT_CAPACITY;
        }

		neutralized = curr == '\\';
		str[strLen++] = curr;
        file.get().get();
        curr = file.get().peek();
	}

	if(strLen == strCap)
		str = alloc.get().realloc(str, strCap, strCap + BETTER_JSON_ARRAY_DEFAULT_CAPACITY);
	str[strLen] = '\0';

    file.get().get(); // Consume the last quote
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseObjectValue(ObjKeyValuePair& objKeyVal)
{
	parseString(objKeyVal.key);

    skipWhitespace();
    if(!file.get().consume(':'))
        throw SyntaxError(file);

	objKeyVal.value = static_cast< PrimVariant* >(alloc.get().malloc(sizeof(PrimVariant)));
	parseAnyPrim(*objKeyVal.value);
}

template< Allocator TAllocator >
void Parser< TAllocator >::parseNumber(PrimVariant& primVariant)
{
	constexpr std::size_t buffSize{64};
	char buffor[buffSize];
	std::size_t inx{};

	bool isFloat{};
	char curr{file.get().peek()};
	while(isdigit(curr) || curr == 'e' || curr == 'E' || curr == '.' || curr == '-' || curr == '+')
	{
		isFloat |= curr == 'e' || curr == 'E' || curr == '.';
		buffor[inx++] = curr;
		if(inx >= buffSize-1)
			throw SyntaxError(file);

        file.get().get();
        curr = file.get().peek();
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
	if(std::isdigit(file.get().peek())) // No good way for encoding this in a switch
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
	skipWhitespace();
	if(!file.get().consume('{'))
		throw SyntaxError(file);

	obj = PrimObject{
		.id = PRIM_OBJECT_ID,
		.size = 0,
		.capacity = 0,
		.elements = nullptr
	};

	skipWhitespace();
	if(file.get().consume('}'))
		return;

	do
	{
		if(obj.size * sizeof(ObjKeyValuePair*) >= obj.capacity)
        {
            obj.elements = alloc.get().realloc(
                obj.elements, 
                obj.capacity, 
                obj.capacity + sizeof(ObjKeyValuePair*) * BETTER_JSON_ARRAY_DEFAULT_CAPACITY);
            obj.capacity += sizeof(ObjKeyValuePair*) * BETTER_JSON_ARRAY_DEFAULT_CAPACITY;
        }

        obj.elements[obj.size] = static_cast< ObjKeyValuePair* >(alloc.get().malloc(sizeof(ObjKeyValuePair)));
		parseObjectValue(*obj.elements[obj.size]);
		obj.size++;

        skipWhitespace();
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
        if(arr.size * sizeof(PrimVariant*) >= arr.capacity)
        {
            arr.elements = alloc.get().realloc(
                arr.elements,
                arr.capacity,
                arr.capacity + sizeof(PrimVariant*) * BETTER_JSON_ARRAY_DEFAULT_CAPACITY);
            arr.capacity += sizeof(PrimVariant*) * BETTER_JSON_ARRAY_DEFAULT_CAPACITY;
        }

        arr.elements[arr.size] = static_cast< PrimVariant* >(alloc.get().malloc(sizeof(PrimVariant)));
		parseAnyPrim(*arr.elements[arr.size]);
		arr.size++;

        skipWhitespace();
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
void Parser< TAllocator >::parseInt(PrimInt& i, char buffor[], const char* end) const
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
void Parser< TAllocator >::parseFloat(PrimFloat& f, char buffor[], const char* end) const
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
void Parser< TAllocator >::parseBool(PrimBool& b) const
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
void Parser< TAllocator >::parseNull(PrimNull& null) const
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

template< Allocator TAllocator >
PrimVariant& Parser< TAllocator >::operator()()
{
    if(used)
        throw std::logic_error("Parser already used for given file.");

    used = true;
    PrimVariant* prim{
        static_cast< PrimVariant* >(alloc.get().malloc(sizeof(PrimVariant)))
    };

    parseAnyPrim(*prim);
    return *prim;
}

template< Allocator TAllocator >
std::shared_ptr< Json > Parser< TAllocator>::parse(File& file)
{
	auto allocator{std::make_shared< DefaultAllocator >(DefaultAllocator{})};
	return JsonVariant(
		Parser<>(*allocator, file)(),
		allocator
		).getJson();
}

template< Allocator TAllocator >
std::shared_ptr< Json > Parser< TAllocator>::parse(File&& file)
{
	auto allocator{std::make_shared< DefaultAllocator >(DefaultAllocator{})};
	return JsonVariant(
		Parser<>(*allocator, file)(),
		allocator
		).getJson();
}

template< Allocator TAllocator >
std::shared_ptr< Json > Parser< TAllocator>::parse(const std::string& str)
{
	Buffer fileBuffer(str.c_str());
	auto allocator{std::make_shared< DefaultAllocator >(DefaultAllocator{})};
	return JsonVariant(
		Parser<>(*allocator, fileBuffer)(),
		allocator
		).getJson();
}

template< Allocator TAllocator >
std::shared_ptr< Json > Parser< TAllocator>::parse(std::istream& stream)
{
	FileStream fileStream(stream);
	auto allocator{std::make_shared< DefaultAllocator >(DefaultAllocator{})};
	return JsonVariant(
		Parser<>(*allocator, fileStream)(),
		allocator
		).getJson();
}

}//namespace json