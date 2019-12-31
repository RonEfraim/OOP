#include "House.h"

//constractor for 2 shapes
House::House(const Rectangle & rectangle, const IsoscelesTriangle & triangle)
	 :m_rec (rectangle.getBottomLeft() , rectangle.getTopRight()),
	  m_tri (triangle.getCenter(), triangle.getLength(), triangle.getHeight())
{
	//check if not in range set defalut values
	if (!check1())
	{
		Vertex temp_tri[] = { {20,20}, {25,25}, {30,20} };

		m_tri = temp_tri;	
		m_rec = { {20,10 }, { 30,20 } };

	}
}

//constractor for one vertex, width, roof height or base height
House::House(const Vertex & roofTop, double width, double roofHeight, double baseHeight)
	:m_rec({ roofTop.m_x - (width / 2), roofTop.m_y - (roofHeight - baseHeight) }, width, baseHeight),
	m_tri({ roofTop.m_x, roofTop.m_y - (roofHeight / 2) }, width, roofHeight)
{
	//check if not in range set defalut values
	if (!check2())
	{
		Vertex temp_tri[] = { {20,20}, {25,25}, {30,20} };

		m_tri = temp_tri;	
		m_rec = { {20,10 }, { 30,20 } };

	}
}

//check if the new width is in range
bool House::extendRoof(double width)
{
	if (width < m_rec.getWidth() && !doubleEqual(m_tri.getLength(), width))

		return false;

	m_tri = IsoscelesTriangle(m_tri.getVertex(1), width, m_tri.getHeight());
	return true;
}

//get height
double House::getHeight() const
{
	return m_rec.getHeight() + m_tri.getHeight();
}

//calculate the difference between the width of trianglea and the width of rectangle
double House::getWidthDifference() const
{
	return m_tri.getLength() - m_rec.getWidth();
}

//drawing the house
void House::draw(Board & board) const
{
	m_rec.draw(board);
	m_tri.draw(board);
}

//calculate area of the house
double House::getArea() const
{
	return m_rec.getArea() + m_tri.getArea();
}

//calculate perimeter
double House::getPerimeter() const
{
	return (m_rec.getPerimeter() + m_tri.getPerimeter());
}

//get center
Vertex House::getCenter() const
{
	Vertex m_center;

	//calc new center
	m_center.m_x = (m_tri.getVertex(0).m_x + m_rec.getTopRight().m_x) / 2;
	m_center.m_y = (m_tri.getVertex(0).m_y + m_rec.getTopRight().m_y) / 2;

	return m_center;
}

//expand house
bool House::scale(double factor)
{
	Vertex m_center = getCenter();
	
	if((m_rec.scale(factor,m_center)) && (m_tri.scale(factor, m_center)))

		return true;

	return false;
}

//bounding func
Rectangle House::getBoundingRectangle() const
{
	Vertex topRight = m_tri.getBoundingRectangle().getTopRight();
	
	return Rectangle(m_tri.getVertex(0), topRight);
}

//check if in range
bool House::check1()
{
	if (sameY(m_tri.getVertex(0), m_rec.getTopRight()) &&
		sameX(m_tri.getVertex(2), m_rec.getTopRight()) &&
		m_tri.getVertex(1).isHigherThan(m_tri.getVertex(0)))	
		
		return true;

	return false;
}

bool House::check2()		
{
	if (sameY(m_tri.getVertex(0), m_rec.getTopRight()) &&
		sameX(m_tri.getVertex(2), m_rec.getBottomLeft()))

		return true;
	
	return false;
}
