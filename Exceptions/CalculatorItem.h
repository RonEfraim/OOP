#pragma once
class CalculatorItem
{
public:
	CalculatorItem() = default;
	virtual ~CalculatorItem() = default;
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual void draw() const = 0;
	virtual void printDetails() const = 0;
};

