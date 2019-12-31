#pragma once

#include "StaticObject.h"

class Present : public StaticObject
{
public:

	Present(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, unsigned int index
		/*, unsigned int bomb_number*/);
	~Present();

private:
	unsigned int m_bomb;

};

