#include "ConfuxException.h"
#include <sstream>

ConfuxException::ConfuxException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* ConfuxException::what() const noexcept
{
	std::ostringstream oss;
	oss << getType() << "\n"
		<< getOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* ConfuxException::getType() const noexcept
{
	return "Confus Exception";
}

int ConfuxException::getLine() const noexcept
{
	return line;
}

const std::string& ConfuxException::getFile() const noexcept
{
	return file;
}

std::string ConfuxException::getOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[FILE]: " << file << "\n" // I don't think I need the flush in std::endl
		<< "[LINE]: " << line;
	return oss.str();
}