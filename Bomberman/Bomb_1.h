#pragma once


#include "StaticObject.h"

class Bomb : public StaticObject 
{
public:
	Bomb(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~Bomb();

	unsigned int getState();
	void bombHandle();
	bool collideHandlerBomb(StaticObject& staticObject);
	unsigned int getType();
	void setState(unsigned int state);
	void setPosition(sf::Vector2f pos);
	
private:
	float m_time;
	sf::Time m_t;
	sf::Clock m_clock;
	unsigned int m_state;
	unsigned int m_type;
};


