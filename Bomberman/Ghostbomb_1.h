
#pragma once
#include "StaticObject.h"
#include "Bomb.h"

class Ghostbomb : public Bomb
{
public:
	Ghostbomb(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~Ghostbomb();

	unsigned int getState();
	void bombHandle() {};
	bool collideHandlerBomb(StaticObject& staticObject);
	unsigned int getType();

private:
	float m_time;
	sf::Time m_t;
	sf::Clock m_clock;
	unsigned int m_state;
	unsigned int m_type;
};


