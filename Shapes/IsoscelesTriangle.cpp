#include "IsoscelesTriangle.h"

//constractor for 3 verticies in array
IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3])
	:m_v{ vertices[0], vertices[1], vertices[2] }
{ 
	//check if in range
	if (!check(m_v[0], m_v[1], m_v[2]))
	{
		m_v[0] = { 20, 20 };
		m_v[1] = { 25, 25 };
		m_v[2] = { 30, 20 };
	}
}

//constractor for a vertex- height and width
IsoscelesTriangle::IsoscelesTriangle(const Vertex & center, double width, double height)
	//give default values for now
	 :m_v{ {20,20}, {25,25}, {20,30} }
{
	Vertex left = { center.m_x - width / 2, center.m_y - height };
	Vertex right = { center.m_x + width / 2, center.m_y - height };

	//if triangle is in range
	if (check(left, center, right))
	{
		m_v[0] = { left };
		m_v[1] = { center }; //center==top
		m_v[2] = { right };
	}

	//else- give triangle default values
}

//get vertex if valid
Vertex IsoscelesTriangle::getVertex(int index) const
{
	if (index < 0 || index > 2)
	{
		std::cerr << "Error: Index number" << index << "is out of range\n";
		exit(EXIT_FAILURE);
	}

	return m_v[index];
}

//get len
double IsoscelesTriangle::getLength() const
{
	return (distance(m_v[0], m_v[2]));
}

//get scale len
double IsoscelesTriangle::getScelesLength() const
{
	return (distance(m_v[0], m_v[1]));
}

//get height
double IsoscelesTriangle::getHeight() const
{
	return (m_v[1].m_y - m_v[2].m_y);
}


//general//

//draw isos triangle
void IsoscelesTriangle::draw(Board & board) const
{
	board.drawLine(m_v[0], m_v[2]);
	board.drawLine(m_v[1], m_v[0]);
	board.drawLine(m_v[2], m_v[1]);
}

//get area
double IsoscelesTriangle::getArea() const
{
	return (getHeight() * getLength());
}

//get perimeter
double IsoscelesTriangle::getPerimeter() const
{
	return (getScelesLength() * 2 + getLength());
}

//get center
Vertex IsoscelesTriangle::getCenter() const
{
	Vertex m_center;

	//calc new center
	m_center.m_x = (m_v[0].m_x + m_v[1].m_x + m_v[2].m_x) / 3;
	m_center.m_y = (m_v[0].m_y + m_v[1].m_y + m_v[2].m_y) / 3;

	return m_center;
}

//expand isos triangle
bool IsoscelesTriangle::scale(double factor)
{
	Vertex m_center = getCenter();
	return scale(factor, m_center);

}

//scale func
bool IsoscelesTriangle::scale(double factor, Vertex m_center)
{
	//new isos triangle
	Vertex new_top;
	Vertex new_left;
	Vertex new_right;

	new_left.m_x = m_v[0].m_x + (factor - 1)*(m_v[0].m_x - m_center.m_x);
	new_left.m_y = m_v[0].m_y + (factor - 1)*(m_v[0].m_y - m_center.m_y);
	new_top.m_x = m_v[1].m_x + (factor - 1)*(m_v[1].m_x - m_center.m_x);
	new_top.m_y = m_v[1].m_y + (factor - 1)*(m_v[1].m_y - m_center.m_y);
	new_right.m_x = m_v[2].m_x + (factor - 1)*(m_v[2].m_x - m_center.m_x);
	new_right.m_y = m_v[2].m_y + (factor - 1)*(m_v[2].m_y - m_center.m_y);

	//if valid
	if (check(new_left, new_top, new_right))
	{
		m_v[0] = new_left;
		m_v[1] = new_top;
		m_v[2] = new_right;
		
		return true;
	}

	return false;
}

//bounding func
Rectangle IsoscelesTriangle::getBoundingRectangle() const
{
	Vertex TopRight,			
		   BottomLeft;

	//if v[1] is up
	if (m_v[1].isHigherThan(m_v[0])) 
	{
		BottomLeft = m_v[0];
		TopRight = { m_v[2].m_x, m_v[1].m_y };
	}

	//if v[1] is down
	else 
	{       
		BottomLeft = { m_v[0].m_x, m_v[1].m_y };
		TopRight = m_v[2];
	}
	
	return Rectangle(BottomLeft, TopRight);
}

//check if in range
bool IsoscelesTriangle::check(const Vertex & v1, const Vertex & v2, const Vertex & v3)
{
	if (v1.isValid() && v2.isRighterThan(v1) 
		&& v2.isValid() && v3.isRighterThan(v2)
		&& v3.isValid() && v3.isRighterThan(v1) &&
		doubleEqual(distance(v1, v2), distance(v2, v3))
		&& !sameX(v1, v3) && !sameY(v1, v2))

		return true;
	
	return false;
	
}
