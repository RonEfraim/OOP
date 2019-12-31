#pragma once
#include "Vertex.h"
#include "macros.h"
#include "Board.h"
#include "Utilities.h"

class Rectangle
{
public:

	Rectangle(const Vertex& bottomLeft, const Vertex& topRight);
	Rectangle(const Vertex vertices[2]);
	Rectangle(double x0, double y0, double x1, double y1);
	Rectangle(const Vertex& start, double width, double height);

	Vertex getBottomLeft() const;
	Vertex getTopRight() const;
	double getWidth() const;
	double getHeight() const;

	//general
	double getArea() const;
	double getPerimeter() const;
	void draw(Board& board) const;
	Vertex getCenter() const;
	bool scale(double factor);
	bool scale(double factor, Vertex m_center);
	Rectangle getBoundingRectangle() const;


private:
	Vertex m_topRight;
	Vertex m_bottomLeft;

	bool check(const Vertex& bottomLeft, const Vertex& topRight);
};


