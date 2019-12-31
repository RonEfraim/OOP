#include "Bomb.h"
#include "macros.h"



Bomb::Bomb(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, const unsigned int index) :
	StaticObject(size, pos, textures, index)
{
	m_type = VBOMB;
	m_clock.restart();
	m_state = BEFORE_EXPLODED;
	//m_rectangle.setOutlineThickness(3);
	//m_rectangle.setOutlineColor(sf::Color::White);
}

void Bomb::bombHandle()
{
	sf::Vector2f size;
	sf::Vector2f change;
	change = m_rectangle.getPosition();
	change.x = change.x + 10;
	change.y = change.y;
	//size.x = 30;
	//size.y = 30;
	m_t = m_clock.getElapsedTime();
	m_time = m_t.asSeconds();

	switch (m_state)
	{
	case BEFORE_EXPLODED:
		if (m_time >= 1)
			updatePicture(V3);
		if (m_time >= 2)
			updatePicture(V2);
		if (m_time >= 3)
			updatePicture(V1);
		if (m_time >= 4)
		{
			m_state = DURING_EXPLODED;
			changeSize({ 60 , 60 });
			m_rectangle.setPosition(change);
			updatePicture(VEXPLODED);
		}
		break;
	case DURING_EXPLODED:
		if (m_time >= 5)
		{
			disable();
			m_state = AFTER_EXPLODED;
		}
		break;
	case AFTER_EXPLODED:
		break;
	}

	
}

unsigned int Bomb::getState()
{
	return m_state;
}

bool Bomb::collideHandlerBomb(StaticObject& staticObject)
{
	bool result;
	if (staticObject.m_objectType == VROCK)
	{
		if (m_state == DURING_EXPLODED)
		{
			m_rectangle.setSize({ 40 ,60 });
			setPosition({0 , -20 });
		}
		result = staticObject.isCollide(m_rectangle.getGlobalBounds());
		if (m_state == DURING_EXPLODED)
		{
			m_rectangle.setSize({ 60,60 });
			backToDefault();
			updatePicture(VEXPLODED);
		}
		if ((result == true) && (isActive() == true))
			return true;
	}
	return false;
}			

void Bomb::setPosition(sf::Vector2f pos)
{
	sf::Vector2f location;
	location = m_rectangle.getPosition();
	location.x += pos.x;
	location.y += pos.y;
	m_rectangle.setPosition(location);
}

unsigned int Bomb::getType()
{
	return m_type;
}

void Bomb::setState(unsigned int state)
{
	m_state = state;
}

Bomb::~Bomb()
{
}
