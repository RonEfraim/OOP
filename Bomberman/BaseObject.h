#pragma once
#include <SFML/Graphics.hpp>
//#include "Robot.h"
//#include "Guard.h"
#include "Wall.h"
#include "Rock.h"
#include "Door.h"
//#include "Present.h"
#include "Bomb.h"
#include "StaticObject.h"
#include "Ghostbomb.h"

class Robot;
class Guard;
class Wall;
class Rock;
//class MySprite;

namespace sf {
	class Color;
	class RenderWindow;
}

class BaseObject
{
public:
	BaseObject() = default;
	virtual ~BaseObject() = default;
	virtual void draw(sf::RenderWindow& renderWindow) const = 0;
	virtual void move(const sf::Vector2f& vector2f,
					  const sf::Vector2f& screenBoundryMin,
					  const sf::Vector2f& screenBoundrymax,
					  sf::Vector2f rbotLocation) = 0;
	virtual void moveRevert() = 0;
	//virtual bool scaleHandler(const sf::Vector2f& coords, float scale) = 0;
	virtual void setToDefault() = 0;
	virtual void uncollideHandler() = 0;
	virtual unsigned int getState() = 0;
	virtual bool isCollide(const sf::FloatRect& rect) const = 0;
	virtual bool collideHandler(BaseObject& baseObject) = 0;
	virtual bool collideHandlerBomb(Bomb& bomb) = 0;
	//virtual bool collideHandlerBombGhost(Ghostbomb& bomb) = 0;
	virtual bool collideHandler(Robot& robot) = 0;
	virtual bool collideHandler(Guard& guard) = 0;
	virtual bool collideHandlerStatic(StaticObject& staticObject) = 0;
	virtual bool collideHandlerStatic(Wall& wall) = 0;
	virtual bool collideHandlerStatic(Rock& rock) = 0;
	virtual bool collideHandlerStatic(Door& door) = 0;
	virtual void changeState() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual void restartPosition() = 0;
	virtual void disable() = 0;
	virtual bool getIsAlive() = 0;
	//virtual bool collideHandler(Wall& wall) = 0;
	//virtual bool collideHandler(Rock& rock) = 0;
	//virtual bool collideHandler(Bomb& bomb) = 0;
	//virtual bool collideHandler(Present& present) = 0;
	bool m_guardCollide;

};

