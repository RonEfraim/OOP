#include "Rectangle.h"
#include <iostream>

//constractor for 2 verticies
Rectangle::Rectangle(const Vertex & bottomLeft, const Vertex & topRight) 
		  : m_bottomLeft(bottomLeft) , m_topRight(topRight) 
{
	//if valid
	check(bottomLeft, topRight);
}

//constractor for 2 verticies in an array
Rectangle::Rectangle(const Vertex vertices[2])
		  : Rectangle(vertices[0], vertices[1])
{
}

//constractor for 4 points
Rectangle::Rectangle(double x0, double y0, double x1, double y1)
	: Rectangle(Vertex{ x0 , y0 }, Vertex{ x1, y1 })
{
}

//constractor for a vertex- starting vertex (height and width)
Rectangle::Rectangle(const Vertex& start, double width, double height)
	: Rectangle(start,{start.m_x + width, start.m_y + height})
{
}

//get bot left
Vertex Rectangle::getBottomLeft() const
{
	return m_bottomLeft;
}

//get top right
Vertex Rectangle::getTopRight() const
{
	return m_topRight;
}

//get width
double Rectangle::getWidth() const
{
	return (m_topRight.m_x - m_bottomLeft.m_x);
}

//get height
double Rectangle::getHeight() const
{
	return (m_topRight.m_y - m_bottomLeft.m_y);
}


//general//

//drawing rec func
void Rectangle::draw(Board& board) const
{
	Vertex m_topLeft;
	Vertex m_bottomRight;

	//create the extra 2 points
	m_topLeft.m_x = m_bottomLeft.m_x;
	m_topLeft.m_y = m_topRight.m_y;
	m_bottomRight.m_x = m_topRight.m_x;
	m_bottomRight.m_y = m_bottomLeft.m_y;

	//send to draw
	board.drawLine(m_bottomRight, m_bottomLeft);//3
	board.drawLine(m_bottomLeft, m_topLeft);	//4
	board.drawLine(m_topRight, m_topLeft);		//1
	board.drawLine(m_topRight, m_bottomRight);	//2
}

//get area
double Rectangle::getArea() const
{
	return (getWidth() * getHeight());
}

//get perimeter
double Rectangle::getPerimeter() const
{
	return (2 * getWidth() + 2 * getHeight());
}

//get center
Vertex Rectangle::getCenter() const
{
	Vertex m_center;

	m_center.m_x = (m_topRight.m_x + m_bottomLeft.m_x) / 2;
	m_center.m_y = (m_topRight.m_y + m_bottomLeft.m_y) / 2;

	return m_center;
}

//expand rec
bool Rectangle::scale(double factor)
{
	Vertex m_center = getCenter();
	//send to scale func
	return scale(factor, m_center);
}

//scale func
bool Rectangle::scale(double factor, Vertex m_center)
{
	//new rec
	Vertex new_top;
	Vertex new_bottom;
	new_top.m_x = m_topRight.m_x + (factor - 1)*(m_topRight.m_x - m_center.m_x);
	new_top.m_y = m_topRight.m_y + (factor - 1)*(m_topRight.m_y - m_center.m_y);
	new_bottom.m_x = m_bottomLeft.m_x + (factor - 1)*(m_bottomLeft.m_x - m_center.m_x);
	new_bottom.m_y = m_bottomLeft.m_y + (factor - 1)*(m_bottomLeft.m_y - m_center.m_y);

	//if in range
	if (new_top.isHigherThan(new_bottom) && new_top.isRighterThan(new_bottom) && new_top.isValid() && new_bottom.isValid())
	{
		m_bottomLeft = new_bottom;
		m_topRight = new_top;
		return true;
	}
	return false;
}

//bounding func
Rectangle Rectangle::getBoundingRectangle() const
{
	return Rectangle(m_bottomLeft,m_topRight);
}

//check if in range
bool Rectangle::check(const Vertex & bottomLeft, const Vertex & topRight)
{
	if (topRight.isHigherThan(topRight) && topRight.isValid()
		&& bottomLeft.isRighterThan(bottomLeft) && bottomLeft.isValid())
	{
		m_topRight = topRight;
		m_bottomLeft = bottomLeft;

		return true;
	}

	return false;
}
