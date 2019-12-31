#pragma once

#include "Rectangle.h"
#include "IsoscelesTriangle.h"
#include "Vertex.h"

class House
{
public:
	House(const Rectangle& rectangle, const IsoscelesTriangle& triangle);
	House(const Vertex& roofTop, double width, double roofHeight, double baseHeight);
	bool extendRoof(double width);
	double getHeight() const;
	double getWidthDifference() const;

	//כללי
	void draw(Board& board) const;
	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
	Rectangle getBoundingRectangle() const;


private:
	Rectangle m_rec;
	IsoscelesTriangle m_tri;
	bool check1();
	bool check2();

};

