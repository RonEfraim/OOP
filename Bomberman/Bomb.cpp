#include "Bomb.h"
#include "macros.h"



Bomb::Bomb(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, const unsigned int index) :
	StaticObject(size, pos, textures, index)
{
	m_type = VBOMB;
	m_clock.restart();
	m_state = BEFORE_EXPLODED;
}

void Bomb::bombHandle(/*sf::RenderWindow& renderWindow*/)
{
	sf::Vector2f size;
	sf::Vector2f change;
	change = m_rectangle.getPosition();
	change.x = change.x + 10;
	change.y = change.y;
	size.x = 100;
	size.y = 100;
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
			changeSize(size);
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
	if(staticObject.m_objectType == VROCK || staticObject.m_objectType == VPRESENETROCK)
		if (staticObject.isCollide(m_rectangle.getGlobalBounds()))
			return true;
	return false;
}			

unsigned int Bomb::getType()
{
	return m_type;
}

Bomb::~Bomb()
{
}
