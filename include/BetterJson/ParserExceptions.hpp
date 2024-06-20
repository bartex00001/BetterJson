#pragma once

#include <exception>
#include <string>

#include <BetterJson/File.hpp>


namespace json
{

class SyntaxError : public std::exception
{
    std::string message;

	SyntaxError(File& buffer, const std::string& info) noexcept;

public:
	static SyntaxError unexpectedCharactrersWhenParsing(File& buffer, char c, const std::string& type);
	static SyntaxError expectedCharacters(File& buffer, const std::string& chars, const std::string& info);
	static SyntaxError constOverflow(File& buffer);

	[[nodiscard]]
	const char* what() const noexcept override;
};


class EndOfInputExpected : public std::exception
{
	std::string message;

public:
	EndOfInputExpected(File& buffer) noexcept;

	[[nodiscard]]
	const char* what() const noexcept override;
};

}//namespace json
