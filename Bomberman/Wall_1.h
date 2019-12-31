#pragma once

#include "StaticObject.h"

class Wall : public StaticObject
{
public:
	Wall(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~Wall();
	
private:
	sf::RectangleShape m_rectangle;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	const sf::Vector2f m_defaultPosition = { 200,100 };
	sf::Vector2f m_originalPosition;
};

