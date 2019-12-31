#include "Ghost.h"

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



Ghost::Ghost(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures)
	: m_rectangle(size), m_index(VGHOST), m_textures(textures)
{
	m_alive = true;
	m_randFrequency = GUARD_RAND_FREQUENCY;
	m_rectangle.setPosition(pos);
	m_originalPosition = pos;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width
		/ 2, m_rectangle.getLocalBounds().height / 2);
}

void Ghost::draw(sf::RenderWindow& renderWindow) const
{
	renderWindow.draw(m_rectangle);
}

void Ghost::move(const sf::Vector2f& vector2f,
	const sf::Vector2f& screenBoundryMin,
	const sf::Vector2f& screenBoundrymax,
	sf::Vector2f rbotLocation)
{
	m_speed--;
	if (m_speed > 0)
		return;
	m_speed = GUARD_SPEED;
	m_randFrequency--;

	float x, y;
	sf::Vector2f guardLocation;
	guardLocation = m_rectangle.getPosition();
	x = abs(guardLocation.x - rbotLocation.x);
	y = abs(guardLocation.y - rbotLocation.y);

	if (y > x )
	{
		if (guardLocation.y > rbotLocation.y)
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

Ghost::~Ghost()
{
}


void Ghost::moveRevert()
{
	m_rectangle.move(m_prevMove);
}

unsigned int Ghost::getState()
{
	return m_state;
}


void Ghost::setToDefault()
{
	m_rectangle.setPosition(m_originalPosition);
	m_rectangle.setScale({ 1, 1 });
}

void Ghost::uncollideHandler()
{
	return;
}

bool Ghost::isCollide(const sf::FloatRect& rect) const
{
	return m_rectangle.getGlobalBounds().intersects(rect);
}

bool Ghost::collideHandler(Robot& robot)
{
	return robot.isCollide(m_rectangle.getGlobalBounds());
}

bool Ghost::collideHandler(Guard& guard)
{
	return guard.isCollide(m_rectangle.getGlobalBounds());
}

bool Ghost::collideHandlerStatic(Wall& wall)
{
	return wall.isCollide(m_rectangle.getGlobalBounds());
}

bool Ghost::collideHandlerStatic(Rock& rock)
{
	return rock.isCollide(m_rectangle.getGlobalBounds());
}

bool Ghost::collideHandlerStatic(Door& door)
{
	return false;
}

bool Ghost::collideHandler(BaseObject& baseObject)
{
	return baseObject.isCollide(m_rectangle.getGlobalBounds());
}

bool Ghost::collideHandlerBomb(Bomb& bomb)
{
	return bomb.isCollide(m_rectangle.getGlobalBounds());
}

bool Ghost::collideHandlerStatic(StaticObject& staticObject)
{
	return false;
}

void Ghost::restartPosition()
{
	m_rectangle.move({ 0 , 0 });
}

void Ghost::disable()
{
	sf::Color color;
	m_rectangle.setFillColor(color.Black);
	m_rectangle.setTexture(NULL);
	m_alive = false;
	m_rectangle.setPosition(m_originalPosition);
}


bool Ghost::getIsAlive()
{
	return m_alive;
}


