#pragma once
#include <exception>
#include <string>


class ConfuxException : public std::exception
{
public:
	ConfuxException(int line, const char* file) noexcept; // TODO: Change file name to string or something not const char*
	const char* what() const noexcept override;
	virtual const char* getType() const noexcept;
	int getLine() const noexcept;
	const std::string& getFile() const noexcept;
	std::string getOriginString() const noexcept;
private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer;
};

