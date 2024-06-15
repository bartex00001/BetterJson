#include <BetterJson/File.hpp>


namespace json
{

Json File::operator()()
{
	// TODO: Call parser and convert one entry into high-level JSON
}

bool File::consume(const char expected)
{
	if(expected == peek())
	{
		get();
		return true;
	}

	return false;
}



char FileBuffer::peek() const
{
	return *buffer;
}

char FileBuffer::get()
{
	if(*buffer == '\n') [[unlikely]]
	{
		lineStart = buffer + 1;
		lineNumber++;
	}

	return *(buffer++);
}

std::size_t FileBuffer::getLineNumber() const
{
	return lineNumber;
}

std::string FileBuffer::getLine()
{
	std::string res{};
	res.reserve(buffer - lineStart + 1);
	for(char* c = lineStart; c != buffer; c++)
		res.push_back(*c);

	return res;
}

FileBuffer::FileBuffer(char* str)
	: lineStart(str),
	  buffer(str)
{
}



char FileStream::peek() const
{
	return lineBuff[linePos];
}

char FileStream::get()
{
	const char current{peek()};
	linePos++;
	lineNumber += (current == '\n');

	if(linePos == BETTER_JSON_LINE_BUFFER_SIZE) [[unlikely]]
	{
		stream.get().get(lineBuff, BETTER_JSON_LINE_BUFFER_SIZE);
		linePos = 0;
	}

	return current;
}

std::size_t FileStream::getLineNumber() const
{
	return lineNumber;
}

std::string FileStream::getLine()
{
	return std::string(lineBuff);
}

FileStream::FileStream(const std::string& fileName)
	: fileStream(std::ifstream(fileName, std::ios::in)),
	  stream(fileStream.value())
{
	if(!fileStream.value().is_open())
		throw std::runtime_error("Could not open file");// TODO: Convert into BetterJson exception
}

FileStream::FileStream(std::istream& stream)
	: stream(stream)
{
}

FileStream::~FileStream()
{
	if(fileStream.has_value())
		fileStream.value().close();
}


}