#pragma once

#include <BetterJson/Prim.hpp>
#include <BetterJson/Allocator.hpp>
#include <BetterJson/File.hpp>


namespace json
{

template< Allocator TAllocator >
class Parser
{
	std::reference_wrapper< TAllocator > alloc;
	std::reference_wrapper< File > file;

	void skipWhitespace();

	void parseString(char*& str);
	void parseObjectValue(ObjKeyValuePair& objKeyVal);
	void parseNumber(PrimVariant& primVariant);

	void parseAnyPrim(PrimVariant& primVariant);

	void parseObject(PrimObject& obj);
	void parseArray(PrimArray& arr);
	void parseString(PrimString& str);
	void parseInt(PrimInt& i, char buffor[], const char* end);
	void parseFloat(PrimFloat& f, char buffor[], const char* end);
	void parseBool(PrimBool& b);
	void parseNull(PrimNull& null);

public:
	Parser(TAllocator& alloc, File& file);
};

}

#include <BetterJson/Parser.tpp>