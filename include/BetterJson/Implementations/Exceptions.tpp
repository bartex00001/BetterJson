#pragma once

#include <BetterJson/Exceptions.hpp>


namespace json
{

inline SyntaxError::SyntaxError(File& buffer) noexcept
{
    message =
		"Syntax error at line\n"
		+ std::to_string(buffer.getLineNumber())
		+ "\t| " + buffer.getLine();
}

inline const char* SyntaxError::what() const noexcept
{
	return message.c_str();
}

}//namespace json
