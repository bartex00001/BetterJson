#include <BetterJson/Exceptions.hpp>

namespace json
{

SyntaxError::SyntaxError(File& buffer) noexcept
	: line(buffer.getLine()),
	  lineNumber(buffer.getLineNumber())
{
}

std::string SyntaxError::what()
{
	return "Syntax error found on line:\n" + std::to_string(lineNumber) + "\t| " + line;
}

}
