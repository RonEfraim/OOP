#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "BaseObject.h"
#include "Board.h"
#include "StaticObject.h"
#include "macros.h"
#include "Bomb.h"
#include "Ghostbomb.h"


class Controller
{
public:
	
	Controller(char *fileName,unsigned int stage);
	~Controller();
	unsigned int getState();
	void setPoints(unsigned int m_totalPoints);
	void setLife(unsigned int m_lifeLeft);
	void setBombs(unsigned int bombs);
	void setTime(float time);
	void setNumOfScreens(unsigned int screens);
	void run();
	unsigned int getPoints();
	unsigned int getLife();
	unsigned int getNumOfBombs();
	float getTime();




private:
	void keyPressedHandler(const sf::Event& event);
	void collideHandler();
	void eventHandler();
	void handleStateChange();
	void updateScreenBoundry();
	void moveObjects();
	void hendelTime();
	void restart();
	void printInfo(char * string);
	void resetRobot();

	sf::RenderWindow m_window;
	std::vector<sf::Texture> m_textures;
	std::vector<std::unique_ptr<BaseObject>> m_gameObjects;
	std::vector<std::unique_ptr<StaticObject>> m_gameStaticObjects;
	std::vector<std::unique_ptr<Bomb>> m_bombsList;
	bool m_isControlPressed = false;
	sf::Vector2f m_robotMove = { 0,0 };
	Board m_board;
	sf::Vector2f m_screenBoundryMax;
	sf::Vector2f m_screenBoundryMin;
	unsigned int m_state = NORMAL;
	sf::Font m_font;
	unsigned int m_points;
	unsigned int m_life ;
	unsigned int m_stage;
	unsigned int m_numOfBombs ;
	unsigned int m_numOfGuards=0;
	float m_time;
	unsigned int m_numOfScreens;
	sf::Time m_t;
	sf::Clock m_clock;
	unsigned int m_robotIndex;
	unsigned int m_rockIndex;
	int m_ghostIndex;
	std::vector<std::unique_ptr<Ghostbomb>> m_ghostBmobList;

};

