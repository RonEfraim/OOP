#pragma once
#include <string>
#include "CalculatorItem.h"

class Shape : public CalculatorItem
{
public:
	Shape(const std::string& name);
	virtual ~Shape() = default;
protected:
	void printName() const;
private:
	std::string m_name;
};

