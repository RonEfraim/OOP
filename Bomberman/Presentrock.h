
#pragma once

#include "StaticObject.h"
#include "Rock.h"
#include "Present.h"

class Presentrock : public StaticObject
{
public:
	Presentrock(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~Presentrock();

private:
	sf::RectangleShape m_rectangle;
	unsigned int m_type;


};
