#pragma once
#include "Vertex.h"
#include "macros.h"
#include "Board.h"
#include <iostream>
#include "Utilities.h"
#include "Rectangle.h"


class IsoscelesTriangle
{
public:
	
	IsoscelesTriangle(const Vertex vertices[3]);
	IsoscelesTriangle(const Vertex& center, double width, double height);
	Vertex getVertex(int index) const;
	double getLength() const;
	double getScelesLength() const;
	double getHeight() const;

	//general
	void draw(Board& board) const;
	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
	bool scale(double factor, Vertex m_center);
	Rectangle getBoundingRectangle() const;

private:

	Vertex m_v[3];
	bool check(const Vertex & v1, const Vertex & v2, const Vertex & v3);

};

