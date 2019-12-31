#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(std::istream& is);
	virtual ~Triangle() = default;
	double area() const override;
	double perimeter() const override;
	void draw() const override;
	void printDetails() const override;

private:
	int m_width;
	int m_height;
};

