#pragma once

#include <BetterJson/File.hpp>
#include <BetterJson/Definitions.hpp>


namespace json
{

inline bool File::consume(const char expected)
{
	if(expected == peek())
	{
		get();
		return true;
	}

	return false;
}

inline char Buffer::peek() const
{
	return *buffer;
}

inline char Buffer::get()
{
	if(*buffer == '\n') [[unlikely]]
	{
		lineStart = buffer + 1;
		lineNumber++;
	}

	return *(buffer++);
}

inline std::size_t Buffer::getLineNumber() const
{
	return lineNumber;
}

inline std::string Buffer::getLine()
{
	std::string res{};
	res.reserve(buffer - lineStart + 1);
	for(const char* c = lineStart; c != buffer; c++)
		res.push_back(*c);

	return res;
}

inline Buffer::Buffer(const char* str)
	: lineStart(str),
	  buffer(str)
{
}


inline char FileStream::peek() const
{
	return lineBuff[linePos];
}

inline char FileStream::get()
{
    const char res = lineBuff[linePos++];
    if(linePos == lineBuff.size())
    {
        linePos = 0;
        std::getline(stream.get(), lineBuff);
        lineNumber++;
    }

    return res;
}

inline std::size_t FileStream::getLineNumber() const
{
	return lineNumber;
}

inline std::string FileStream::getLine()
{
	return {lineBuff};
}

inline FileStream::FileStream(const std::string& fileName)
	: fileStream(std::ifstream(fileName, std::ios::in)),
	  stream(fileStream.value())
{
	if(!fileStream.value().is_open())
		throw std::runtime_error("Could not open file");

    lineBuff.reserve(BETTER_JSON_LINE_BUFFER_SIZE);
    std::getline(stream.get(), lineBuff);
}

inline FileStream::FileStream(std::istream& stream)
	: stream(stream)
{
    lineBuff.reserve(BETTER_JSON_LINE_BUFFER_SIZE);
    std::getline(stream, lineBuff);
}

inline FileStream::~FileStream()
{
	if(fileStream.has_value())
		fileStream.value().close();
}

}//namespace json
