#pragma once

#include "Controller.h"
#include <memory>
#include <vector>

class Bomberman
{
public:
	Bomberman::Bomberman();
	~Bomberman();

	void addController(char *fileName);
	bool run(unsigned int firstTime);
	

private:
	std::vector<std::unique_ptr<Controller>> m_controllers;
	
	unsigned int m_numOfScreens;
	unsigned int m_activeScreen;
	unsigned int m_totalPoints;
	unsigned int m_lifeLeft;
	unsigned int m_bombsLeft;
	float m_timeLeft;
	unsigned int m_stage;
	unsigned int moveToNextScreen();
	sf::RenderWindow m_window;
	std::vector<sf::Texture> m_textures;
	sf::Font m_font;
	Board m_board;
	sf::RectangleShape m_endgame;
	sf::RectangleShape m_start;
	int hendelEndStartGame();
	int MousePressedHandler(sf::Event event);
	void saveDataToNextScrean();
};

