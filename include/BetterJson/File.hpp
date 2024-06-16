#pragma once

#include <cstddef>
#include <functional>
#include <istream>
#include <fstream>
#include <optional>
#include <string>

#ifndef BETTER_JSON_LINE_BUFFER_SIZE
#define BETTER_JSON_LINE_BUFFER_SIZE 128
#endif


namespace json
{

class File {
public:
	virtual char peek() const = 0;
	virtual char get() = 0;
	bool consume(const char expected);

	virtual std::size_t getLineNumber() const = 0;
	virtual std::string getLine() = 0;
};


class FileBuffer final : public File
{
	const char* lineStart{};
	const char* buffer{};
	std::size_t lineNumber{1};

public:
	char peek() const override;
	char get() override;

	std::size_t getLineNumber() const override;
	std::string getLine() override;

	FileBuffer(const char* str);
};


class FileStream final : public File
{
	char lineBuff[BETTER_JSON_LINE_BUFFER_SIZE]{0};
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

	~FileStream();
};

}

#include <BetterJson/Implementations/File.tpp>
