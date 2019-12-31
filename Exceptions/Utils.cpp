#include "Utils.h"
#include "Exceptions.h"
#include <iostream>


int Utils::readInt(std::istream& is)
{
	try{
	int number;
	is >> number;
	if (number < 0 /*|| !(isdigit(number))*/)
		throw(WrongNum());
	return number;
	}
	catch (exception &c)
	{
		std::cout << std::endl << c.what()<< std::endl;
	}
}