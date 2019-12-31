
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

#pragma once

//#include "Vertex.h"
//#include "Board.h"
//#include "MovingImage.h"
//#include "ObjectLife.h"
#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "Guard.h"
#include "Object.h"
#include "Door.h"
#include "macros.h"
#include "Ghostbomb.h"

class Robot;
class Door;

//==========================Class Robo==============================

class Guard : public BaseObject
{
public:
	 
	Guard(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures);
	
	void draw(sf::RenderWindow& renderWindow) const override;
	void move(const sf::Vector2f& vector2f,
			  const sf::Vector2f& screenBoundryMin,
			  const sf::Vector2f& screenBoundrymax,
				sf::Vector2f rbotLocation) override;
	void moveRevert() override;
	void changeState() {};
	void setSize(const sf::Vector2f& size) {};
	void setPosition(sf::Vector2f pos) {};
	unsigned int getState() override;
	void setToDefault() override;
	void uncollideHandler() override;
	bool isCollide(const sf::FloatRect& rect) const override;
	bool collideHandler(Robot& robot) override;
	bool collideHandler(Guard& guard) override;
	bool collideHandlerStatic(Wall& wall) override;
	bool collideHandlerStatic(Rock& rock) override;
	bool collideHandlerStatic(Door& door) override;
	bool collideHandler(BaseObject& baseObject) override;
	bool collideHandlerStatic(StaticObject& staticObject) override;
	bool collideHandlerBomb(Bomb& bomb) override;
	//bool collideHandlerBombGhost(Ghostbomb& bomb) override;
	unsigned int m_speed = 2;
	void disable();
	sf::Vector2f getPosition() 
	{
		sf::Vector2f a;
		return a;
	};
	void restartPosition();
	bool getIsAlive();
	

private:
	// keeps all the points the robot got in the screen
	// it also get the points from the previous screen
	unsigned int m_points;
	sf::RectangleShape m_rectangle;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	const sf::Vector2f m_defaultPosition = { 200,100 };
	sf::Vector2f m_originalPosition;
	sf::Vector2f m_prevMove;
	unsigned int m_randFrequency;
	unsigned int m_state = NORMAL;
	sf::Vector2f m_guardRestart;
	bool m_alive;
	bool m_smart;
	bool m_moveRevert;

};

