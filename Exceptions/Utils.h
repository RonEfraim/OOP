#pragma once
#include <istream>

class Utils
{
public:
	Utils() = delete;
	~Utils() = delete;
	static int readInt(std::istream& is);
};

