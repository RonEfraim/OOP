#pragma once
#include <fstream>
#include <iostream>
#include "utilities.h"
#include "GraphicsManager.h"
#include <SFML/Graphics.hpp>
#include "ToolBar.h"


class Map
{
public:
	Map();
	Map(std::fstream &);
	void run();
	void read(int&, int&);
	void fNew(const char &, sf::Vector2i);
	~Map();

private:
	int m_row = 0;
	int m_col = 0;
	void print();
	sf::Vector2i inGrid(const sf::Vector2i &);
	void save();
	void event();
	void drawScreen(sf::RenderWindow &);
	sf::RenderWindow m_window;
	ToolBar m_tool;
	sf::Vector2f m_initialGrid;
	std::vector<std::vector<Objects*>> m_objects;
	int m_currentClicked;
	int clickedToolbarIndex;
};

