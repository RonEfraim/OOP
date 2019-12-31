#pragma once
#include <exception>

class FileException :public std::exception
{
public:
	
	virtual char const* what() const override { return "Error opening File\n"; }
};