#pragma once

#include <BetterJson/ParserExceptions.hpp>


namespace json
{

inline SyntaxError::SyntaxError(File& buffer, const std::string& info) noexcept
{
    message =
    	info
		+ " at line\n"
		+ std::to_string(buffer.getLineNumber())
		+ "\t| " + buffer.getLine();
}

inline SyntaxError SyntaxError::unexpectedCharactrersWhenParsing(File& buffer, char c, const std::string& type)
{
	std::string symbol{};
	switch(c)
	{
	case EOF:
		symbol = "EOF";
		break;
	case '\0':
		symbol = "\\0";
		break;
	case '\n':
		symbol = "\\n";
		break;
	case '\t':
		symbol = "\\t";
		break;
	case '\r':
		symbol = "\\r";
		break;
	default:
		symbol = c;
	}

	return {
		buffer,
		"Started parsing '"
		+ type
		+ "', but found unexpected character: '" + symbol + "'"
	};
}

inline SyntaxError SyntaxError::expectedCharacters(File& buffer, const std::string& chars, const std::string& info)
{
	return {
		buffer,
		"Expected symbol '"
		+ chars
		+ "', "
		+ info
	};
}

inline SyntaxError SyntaxError::constOverflow(File& buffer)
{
	return {
		buffer,
		"Constant too large (will overflow)"
	};
}



inline const char* SyntaxError::what() const noexcept
{
	return message.c_str();
}


inline EndOfInputExpected::EndOfInputExpected(File& buffer) noexcept
{
	message =
		"Expected end of input, but found: \n"
		+ std::to_string(buffer.getLineNumber())
		+ "\t| " + buffer.getLine();
}

inline const char* EndOfInputExpected::what() const noexcept
{
	return message.c_str();
}

}//namespace json
