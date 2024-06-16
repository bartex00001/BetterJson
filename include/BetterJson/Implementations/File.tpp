#include <BetterJson/File.hpp>


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



inline char FileBuffer::peek() const
{
	return *buffer;
}

inline char FileBuffer::get()
{
	if(*buffer == '\n') [[unlikely]]
	{
		lineStart = buffer + 1;
		lineNumber++;
	}

	return *(buffer++);
}

inline std::size_t FileBuffer::getLineNumber() const
{
	return lineNumber;
}

inline std::string FileBuffer::getLine()
{
	std::string res{};
	res.reserve(buffer - lineStart + 1);
	for(const char* c = lineStart; c != buffer; c++)
		res.push_back(*c);

	return res;
}

inline FileBuffer::FileBuffer(const char* str)
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
    if(lineBuff[linePos] == '\0') [[unlikely]]
    {
        linePos = 0;
        stream.get().getline(lineBuff, BETTER_JSON_LINE_BUFFER_SIZE);
    }

    if(res == '\n') [[unlikely]]
        lineNumber++;

    return res;
}

inline std::size_t FileStream::getLineNumber() const
{
	return lineNumber;
}

inline std::string FileStream::getLine()
{
	return std::string(lineBuff);
}

inline FileStream::FileStream(const std::string& fileName)
	: fileStream(std::ifstream(fileName, std::ios::in)),
	  stream(fileStream.value())
{
	if(!fileStream.value().is_open())
		throw std::runtime_error("Could not open file");// TODO: Convert into BetterJson exception

    stream.get().getline(lineBuff, BETTER_JSON_LINE_BUFFER_SIZE);
}

inline FileStream::FileStream(std::istream& stream)
	: stream(stream)
{
    stream.getline(lineBuff, BETTER_JSON_LINE_BUFFER_SIZE);
}

inline FileStream::~FileStream()
{
	if(fileStream.has_value())
		fileStream.value().close();
}


}