#pragma once

#include <exception>
#include <string>

#include <BetterJson/File.hpp>


namespace json
{

class SyntaxError : public std::exception
{
    std::string message;

public:
	SyntaxError(File& buffer) noexcept;

	[[nodiscard]]
	const char* what() const noexcept override;
};

}//namespace json
