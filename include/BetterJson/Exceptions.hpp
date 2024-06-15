#pragma once

#include <exception>
#include <string>

#include <BetterJson/File.hpp>


namespace json
{

class SyntaxError : std::exception
{
protected:
	std::string line;
	std::size_t lineNumber;


public:
	SyntaxError(File& buffer) noexcept;

	std::string what();
};

}
