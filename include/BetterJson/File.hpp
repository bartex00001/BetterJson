#pragma once

#include <cstddef>
#include <functional>
#include <istream>
#include <fstream>
#include <optional>
#include <string>


namespace json
{

class File {
public:
	virtual ~File() = default;

	[[nodiscard]]
	virtual char peek() const = 0;
	virtual char get() = 0;
	bool consume(char expected);

	[[nodiscard]]
	virtual std::size_t getLineNumber() const = 0;
	virtual std::string getLine() = 0;
};


class Buffer final : public File
{
	const char* lineStart{};
	const char* buffer{};
	std::size_t lineNumber{1};

public:
	[[nodiscard]]
	char peek() const override;
	char get() override;

	[[nodiscard]]
	std::size_t getLineNumber() const override;
	std::string getLine() override;

	Buffer(const char* str);
};


class FileStream final : public File
{
	std::string lineBuff;
	std::size_t linePos{};
	std::size_t lineNumber{1};

	std::optional< std::ifstream > fileStream{};
	std::reference_wrapper< std::istream > stream;

public:
	char peek() const override;
	char get() override;

	std::size_t getLineNumber() const override;
	std::string getLine() override;

	FileStream(const std::string& fileName);
	FileStream(std::istream& stream);

	~FileStream() override;
};

}//namespace json
