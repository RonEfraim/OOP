#pragma once

#include "StaticObject.h"

class Rock : public StaticObject
{
public:
	Rock(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~Rock();

	

private:
	sf::RectangleShape m_rectangle;
	unsigned int m_type;
	
	
};

