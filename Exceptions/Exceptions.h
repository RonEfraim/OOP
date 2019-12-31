#pragma once
#include <exception>

using std::exception;

class WrongCommand : public exception
{
	char const* what() const override { return "Wrong command\n"; }
};

class OutOfRange : public exception
{
	char const* what() const override { return "Out of range\n"; }
};

class InvalidChar : public exception
{
	char const* what() const override { return "Invalid char\n"; }
};

class WrongNum : public exception
{
	char const* what() const override { return "Wrong Number\n"; }
};

class ToManyShapes : public exception
{
	char const* what() const override { return "To many shapes\n"; }
};

class SmallNum : public exception
{
	char const* what() const override { return "The number is to small \n"; }
};

class Failed : public exception
{
	char const* what() const override { return "File does not open\n"; }
};
