#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
class Objects
{
public:
	Objects() = delete;
	Objects(const sf::Texture* t, const char&s, const sf::Vector2f pos);
	bool contains(sf::Vector2f pos);
	void draw(sf::RenderWindow & window, sf::Vector2f pos = { -1,-1 });
	char getChar() const;
	~Objects();

private:
	const char m_symbol;
	const sf::Texture* m_texture;
	sf::Vector2f m_pos;
};