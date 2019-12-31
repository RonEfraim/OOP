
#pragma once

#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "Guard.h"
#include "Object.h"
#include "Door.h"
#include "macros.h"
#include "Ghostbomb.h"



class Ghost : public BaseObject
{
public:

	Ghost(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures);
	~Ghost();
	void draw(sf::RenderWindow& renderWindow) const override;
	void move(const sf::Vector2f& vector2f,
		const sf::Vector2f& screenBoundryMin,
		const sf::Vector2f& screenBoundrymax,
		sf::Vector2f rbotLocation) override;
	void moveRevert() override;
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
	unsigned int m_speed = 2;
	void setSize(const sf::Vector2f& size) {};
	void setPosition(sf::Vector2f pos) {};
	void changeState() {};
	void disable();
	
	sf::Vector2f getPosition()
	{
		sf::Vector2f a;
		return a;
	};
	void restartPosition();
	bool getIsAlive();


private:
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

