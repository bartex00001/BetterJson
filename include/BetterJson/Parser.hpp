#pragma once

#include <BetterJson/Allocator.hpp>
#include <BetterJson/File.hpp>
#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/Prim.hpp>


namespace json
{

template< Allocator TAllocator = DefaultAllocator >
class Parser
{
	std::reference_wrapper< TAllocator > alloc;
	std::reference_wrapper< File > file;
    bool used{};

	void skipWhitespace();

	void parseString(char*& str);
	void parseObjectValue(ObjKeyValuePair& objKeyVal);
	void parseNumber(PrimVariant& primVariant);

	void parseAnyPrim(PrimVariant& primVariant);

	void parseObject(PrimObject& obj);
	void parseArray(PrimArray& arr);
	void parseString(PrimString& str);
	void parseInt(PrimInt& i, char buffor[], const char* end) const;
	void parseFloat(PrimFloat& f, char buffor[], const char* end) const;
	void parseBool(PrimBool& b) const;
	void parseNull(PrimNull& null) const;

public:
	Parser(TAllocator& alloc, File& file);
    PrimVariant& operator()();

	static std::shared_ptr< Json > parse(File& file);
	static std::shared_ptr< Json > parse(File&& file);
	static std::shared_ptr< Json > parse(const std::string& str);
	static std::shared_ptr< Json > parse(std::istream& stream);
};

}//namespace json
