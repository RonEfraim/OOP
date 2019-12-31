#include "Kite.h"

//constractor for 2 verticies in an array
Kite::Kite(const IsoscelesTriangle triangles[2])
	:m_tri1(triangles[0]), m_tri2(triangles[1])
{
	//check if not in range set defalut values
	if (!check())
	{
		Vertex temp_tri1[] = { {20,20}, {25,25}, {30,20} };
		Vertex temp_tri2[] = { {20,20}, {25,15}, {30,20} };

		m_tri1 = IsoscelesTriangle(temp_tri1);
		m_tri2 = IsoscelesTriangle(temp_tri2);
	}
}

//constractor for one vertex, width, top height or bottom height
Kite::Kite(const Vertex & top, double width, double topHeight, double bottomHeight)
	:m_tri1(top, width, topHeight), 
	 m_tri2({top.m_x, top.m_y - (topHeight - bottomHeight)}, width, bottomHeight)
{
	//check if not in range set defalut values
	if (!check())
	{
		Vertex temp_tri1[] = { {20,20}, {25,25}, {30,20} };
		Vertex temp_tri2[] = { {20,20}, {25,15}, {30,20} };

		m_tri1 = IsoscelesTriangle(temp_tri1);
		m_tri2 = IsoscelesTriangle(temp_tri2);
	}
}

//get height of kite
double Kite::getTotalHeight() const	
{
	return distance(m_tri1.getVertex(1), m_tri2.getVertex(1));
}

//draw kite
void Kite::draw(Board & board) const
{
	m_tri1.draw(board);
	m_tri2.draw(board);
}

//get area
double Kite::getArea() const
{
	return (m_tri1.getArea() + m_tri2.getArea());
}

//get perimeter
double Kite::getPerimeter() const
{
	return (m_tri1.getPerimeter() + m_tri2.getPerimeter());
}

//get center
Vertex Kite::getCenter() const
{
	Vertex m_center;

	m_center.m_x = m_tri1.getVertex(1).m_x;
	m_center.m_y = m_tri1.getVertex(0).m_y;

	return m_center;
}

//expand kite
bool Kite::scale(double factor)
{
	Vertex m_center = getCenter();

	if ((m_tri1.scale(factor, m_center)) && (m_tri2.scale(factor, m_center)))
		return true;

	return false;
}

//bounding func
Rectangle Kite::getBoundingRectangle() const
{
	//new points
	Vertex topRight = m_tri1.getBoundingRectangle().getTopRight();
	Vertex bottomLeft = m_tri2.getBoundingRectangle().getBottomLeft();

	return Rectangle(bottomLeft, topRight);
}

//check if in range
bool Kite::check()
{
	if (sameX(m_tri1.getVertex(1), m_tri2.getVertex(1)) &&
		sameY(m_tri1.getVertex(0), m_tri2.getVertex(2)) &&
		m_tri1.getVertex(0).isEqual(m_tri2.getVertex(0)) && 
		doubleEqual(m_tri1.getLength(), m_tri2.getLength()) && 
		m_tri1.getVertex(1).isHigherThan(m_tri2.getVertex(1)))
		return true;

	return false;
}
