
#pragma once
#include "IsoscelesTriangle.h"
#include "Utilities.h"

class Kite
{
public:
	Kite(const IsoscelesTriangle triangles[2]);
	Kite(const Vertex& top, double width, double topHeight, double bottomHeight);
	double getTotalHeight() const;

	//general
	void draw(Board& board) const;
	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
	Rectangle getBoundingRectangle() const;

private:
	IsoscelesTriangle m_tri1;
	IsoscelesTriangle m_tri2;
	bool check();
};

