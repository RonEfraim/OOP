#pragma once
#include "Utilities.h"

#include "Objects.h"

class ToolBar
{
public:
	void build(sf::RenderWindow &m_window);
	bool in_toolbar(sf::Vector2i);
	int clickedOn(const sf::Vector2i &pos);
	const char getCharByIndex(int i)const { return m_char_vector[i]; }
	ToolBar();
	~ToolBar();

private:
	std::vector<Objects *> m_objects;
	sf::Vector2i m_initialPos;
	std::vector<char> m_char_vector;
};