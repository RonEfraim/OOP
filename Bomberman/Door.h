#pragma once

#include "StaticObject.h"

class Door : public StaticObject
{
public:
	Door(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);

	~Door();
};

