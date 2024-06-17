#pragma once

#include <BetterJson/Exceptions.hpp>


namespace json
{

inline SyntaxError::SyntaxError(File& buffer) noexcept
	: line(buffer.getLine()),
	  lineNumber(buffer.getLineNumber())
{
    message = "Syntax error at line\n" + std::to_string(lineNumber) + "\t| " + line;
}

inline const char* SyntaxError::what() const noexcept
{
	return message.c_str();
}

}//namespace json
