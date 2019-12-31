/*

Class Guard
This class is managing the Robot
it is not aware of the game only of itself
It has the following data strauctures:
m_image of class MovingImage which takes care of location management
unisgned int m_points holds the total points of the robot
unisgned int m_lifeLeft holds the number of life that are left
bool m_gameOver - becomes true after m_lifeLeft is 0

*/

//=============================include=======================================

#include "Guard.h"
#include "macros.h"
#include "Robot.h"
#include "Rock.h"
#include "Wall.h"
#include <cmath>
#include "Ghostbomb.h"



Guard::Guard(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures)
	: m_rectangle(size), m_index(VGUARD), m_textures(textures)
{
	m_guardCollide = false;
	m_smart = rand() % 2;
	m_alive = true;
	m_randFrequency = GUARD_RAND_FREQUENCY;
	m_rectangle.setPosition(pos);
	m_originalPosition = pos;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
}

void Guard::draw(sf::RenderWindow& renderWindow) const
{
	renderWindow.draw(m_rectangle);
}

void Guard::move(const sf::Vector2f& vector2f,
				 const sf::Vector2f& screenBoundryMin,
				 const sf::Vector2f& screenBoundrymax,
					sf::Vector2f rbotLocation)
{
	if (m_alive)
	{
		m_speed--;
		if (m_speed > 0)
			return;
		m_speed = GUARD_SPEED;
		m_randFrequency--;

		if (m_smart == false)
		{
			if (m_randFrequency == 0)
			{
				m_randFrequency = GUARD_RAND_FREQUENCY;
				switch ((rand() % 4) + 1)
				{
				case UP:
					m_rectangle.move({ 0, -5 });
					m_prevMove = { 0, 5 };
					break;
				case DOWN:
					m_rectangle.move({ 0, 5 });
					m_prevMove = { 0, -5 };
					break;
				case LEFT:
					m_rectangle.move({ -5, 0 });
					m_prevMove = { 5 , 0 };
					break;
				case RIGHT:
					m_rectangle.move({ 5 , 0 });
					m_prevMove = { -5 , 0 };
					
					break;
				}
			}
			else
			{
				sf::Vector2f next;
				next.x = m_prevMove.x * -1;
				next.y = m_prevMove.y * -1;
				m_rectangle.move(next);
			}
		}

		if (m_smart)
		{
			float x, y;
			sf::Vector2f guardLocation;
			guardLocation = m_rectangle.getPosition();
			x = abs(guardLocation.x - rbotLocation.x);
			y = abs(guardLocation.y - rbotLocation.y);

			if (y > x && m_guardCollide == false)
			{
				if (guardLocation.y > rbotLocation.y )
				{
					m_rectangle.move({ 0, -5 });
					m_prevMove = { 0, 5 };
				}
				else
				{
					m_rectangle.move({ 0, 5 });
					m_prevMove = { 0, -5 };
				}

			}
			else
			{
				if (m_guardCollide == false)
				{
					if (guardLocation.x > rbotLocation.x)
					{
						m_rectangle.move({ -5, 0 });
						m_prevMove = { 5 , 0 };
					}
					else
					{
						m_rectangle.move({ 5 , 0 });
						m_prevMove = { -5 , 0 };
					}
				}
				
			}
			if (m_guardCollide)
			{
				m_guardCollide = false;

				
				switch ((rand() % 4) + 1)
				{
				case UP:
					m_rectangle.move({ 0, -5 });
					m_prevMove = { 0, 5 };
					break;
				case DOWN:
					m_rectangle.move({ 0, 5 });
					m_prevMove = { 0, -5 };
					break;
				case LEFT:
					m_rectangle.move({ -5, 0 });
					m_prevMove = { 5 , 0 };
					break;
				case RIGHT:
					m_rectangle.move({ 5 , 0 });
					m_prevMove = { -5 , 0 };

					break;
				}

			}

		}
		sf::Vector2f location;
		location = m_rectangle.getPosition();
		if (!(location.x <= screenBoundrymax.x && location.x >= screenBoundryMin.x) ||
			!(location.y <= screenBoundrymax.y && location.y >= screenBoundryMin.y))
				moveRevert();
	}

}


void Guard::moveRevert()
{
	m_rectangle.move(m_prevMove);
}

unsigned int Guard::getState()
{
	return m_state;
}


void Guard::setToDefault()
{
	m_rectangle.setPosition(m_originalPosition);
	m_rectangle.setScale({ 1, 1 });
}

void Guard::uncollideHandler()
{
	return;
}

bool Guard::isCollide(const sf::FloatRect& rect) const
{
	return m_rectangle.getGlobalBounds().intersects(rect);
}

bool Guard::collideHandler(Robot& robot)
{
	return robot.isCollide(m_rectangle.getGlobalBounds());
}

bool Guard::collideHandler(Guard& guard)
{
	return guard.isCollide(m_rectangle.getGlobalBounds());
}

bool Guard::collideHandlerStatic(Wall& wall)
{
	return wall.isCollide(m_rectangle.getGlobalBounds());
}

bool Guard::collideHandlerStatic(Rock& rock)
{
	return rock.isCollide(m_rectangle.getGlobalBounds());
}

bool Guard::collideHandlerStatic(Door& door)
{
	return false;
}

bool Guard::collideHandler(BaseObject& baseObject)
{
	return baseObject.isCollide(m_rectangle.getGlobalBounds());
}

bool Guard::collideHandlerBomb(Bomb& bomb)
{
	return bomb.isCollide(m_rectangle.getGlobalBounds());
}

bool Guard::collideHandlerStatic(StaticObject& staticObject)
{
	if (staticObject.isCollide(m_rectangle.getGlobalBounds()))
	{
		switch (staticObject.m_objectType)
		{
		case VDOOR:
			return false;
			break;
		case VPRESENT:
			return false;
			break;
		case VBOMB:
			return false;
			break;
		case VROCK:
			if (staticObject.isActive())
				return true;
			return false;
			break;
		}
		return true;
	}
	return false;
}

void Guard::restartPosition()
{
	m_rectangle.move({ 0 , 0 });
}

//bool Robot::collideHandler(Wall& wall);
//bool Robot::collideHandler(Rock& rock);
//bool Robot::collideHandler(Bomb& bomb);
//bool Robot::collideHandler(Present& present);


void Guard::disable()
{
	sf::Color color;
	m_rectangle.setFillColor(color.Black);
	m_rectangle.setTexture(NULL);
	m_alive = false;
	m_rectangle.setPosition(m_originalPosition);
}
	

bool Guard::getIsAlive()
{
	return m_alive;
}


//bool Guard::collideHandlerBombGhost(Ghostbomb& bomb)
//
//	return false;
//}