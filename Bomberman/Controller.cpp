
#define _CRT_SECURE_NO_WARNINGS

#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "macros.h"
#include "Guard.h"
#include "Robot.h"
#include "Wall.h"
#include "Rock.h"
#include "Door.h"
#include "Present.h"
#include <time.h>
#include <Windows.h>
#include "Bomb.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "Ghost.h"
#include "Ghostbomb.h"



void Controller::eventHandler()
{
	sf::Event event{};
	bool result = false;
	result = m_window.pollEvent(event);
	if (result == false)
	{
		collideHandler();
		return;
	}

	switch (event.type)
	{
	case sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::KeyPressed:
		keyPressedHandler(event);
		break;
	default:
		break;
	}
	if (m_state == GAME_OVER || m_state == ROBOT_FOUND_DOOR)
		return;
	collideHandler();
}

Controller::Controller(char *fileName,unsigned int stage) : 
						m_window(sf::VideoMode(800, 800), "Bomberman"),
							m_textures(18), m_board(fileName)
{
	
		m_ghostIndex = -1;
		m_points = 0;
		m_life = 5;
		m_stage = stage;
		m_numOfBombs = m_board.boardInfo(BOMBS);

		if (m_board.getTime() != -1)
			m_time = m_board.getTime();

	sf::Vector2f pos;
	m_window.setVisible(false);
	
	

	m_font.loadFromFile("Gabriola.TTF");
	if ( !m_textures[VROBOT].loadFromFile("robot.png")
		|| !m_textures[VGUARD].loadFromFile("guard.png")
		|| !m_textures[VWALL].loadFromFile("wall.png")
		|| !m_textures[VROCK].loadFromFile("Rock.png")
		|| !m_textures[VDOOR].loadFromFile("door.png")
		|| !m_textures[VPRESENT].loadFromFile("present.png")
		|| !m_textures[VBOMB].loadFromFile("bomb.png")
		|| !m_textures[VEXPLODED].loadFromFile("exploded.gif")
		|| !m_textures[V1].loadFromFile("1.png")
		|| !m_textures[V2].loadFromFile("2.png")
		|| !m_textures[V3].loadFromFile("3.png")
		|| !m_textures[VGHOST].loadFromFile("ghost.png")
		|| !m_textures[VGHOSTBOMB].loadFromFile("ghostbomb.png")
		|| !m_textures[VPRESENETROCK].loadFromFile("rock.png")
		)

	{
		m_window.close();
		return;
	}

	updateScreenBoundry();

	for (int i = 0; i < m_board.boardInfo(LINES); i++)
	{
		for (int j = 0; j < m_board.boardInfo(COLUMNS); j++)
		{
			pos = { (float) j * RECT_SIZE + SCREEN_MIN_X , 
					(float) i * RECT_SIZE + SCREEN_MIN_Y };
			switch (m_board.getChar(i, j))
			{
			case ROBOT:
				m_robotIndex = m_gameObjects.size();
				m_gameObjects.push_back(std::make_unique<Robot,
										const sf::Vector2f&, 
										const sf::Vector2f&, 
										std::vector<sf::Texture>& >
										({ RECT_SIZE, RECT_SIZE }, pos, m_textures));
				break;
			case GUARD:
				m_gameObjects.push_back(std::make_unique<Guard, 
										const sf::Vector2f&, 
										const sf::Vector2f&, 
										std::vector<sf::Texture>& >
									({ RECT_SIZE, RECT_SIZE }, pos, m_textures));
				m_numOfGuards++;
				break;
			case GHOST:
				m_ghostIndex = m_gameObjects.size();
				m_gameObjects.push_back(std::make_unique<Ghost,
										const sf::Vector2f&,
										const sf::Vector2f&,
										std::vector<sf::Texture>& >
									({ RECT_SIZE, RECT_SIZE }, pos, m_textures));
			case WALL:
				m_gameStaticObjects.push_back(std::make_unique<Wall,
											  const sf::Vector2f&,
											  const sf::Vector2f&,
											  std::vector<sf::Texture>&,
											  const unsigned int&>
											 ({ RECT_SIZE, RECT_SIZE }, pos,
											  m_textures,VWALL));
				break;
			case ROCK:
				m_rockIndex = m_gameStaticObjects.size();
				m_gameStaticObjects.push_back(std::make_unique<Rock,
											const sf::Vector2f&,
											const sf::Vector2f&,
											std::vector<sf::Texture>&,
											const unsigned int>
											({ RECT_SIZE, RECT_SIZE }, pos,
											m_textures, VROCK));
				break;
			case EXIT_DOOR:
				m_gameStaticObjects.push_back(std::make_unique<Door,
											const sf::Vector2f&,
											const sf::Vector2f&,
											std::vector<sf::Texture>&,
											const unsigned int>
											({ RECT_SIZE, RECT_SIZE }, pos,
											m_textures, VDOOR));
				break;
			case PRESENT:
				
				m_gameStaticObjects.push_back(std::make_unique<Present,
											const sf::Vector2f&,
											const sf::Vector2f&,
											std::vector<sf::Texture>&,
											const unsigned int>
											({ RECT_SIZE, RECT_SIZE }, pos,
											m_textures, VPRESENT));

				break;
			case PRESENT_ROCK:
				m_gameStaticObjects.push_back(std::make_unique<Rock,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int>
					({ RECT_SIZE, RECT_SIZE }, pos,
						m_textures, VPRESENETROCK));


				break;
			}
		}
	}	
}

void Controller::updateScreenBoundry()
{
	m_screenBoundryMin.x = SCREEN_MIN_X ;
	m_screenBoundryMin.y = SCREEN_MIN_Y ;
	m_screenBoundryMax.x = (m_board.boardInfo(COLUMNS)-1) * RECT_SIZE + SCREEN_MIN_X;
	m_screenBoundryMax.y = (m_board.boardInfo(LINES)-1) * RECT_SIZE + SCREEN_MIN_Y;
}


Controller::~Controller() = default;

void Controller::run()
{
	if (m_board.getTime()!= -1)
		m_clock.restart();
	
	m_window.setVisible(true);
	unsigned int x = m_screenBoundryMax.x + 600, y = m_screenBoundryMax.y;
	m_window.setSize({ x,y });
	while (m_window.isOpen())
	{
		if (m_board.getTime() != -1)
			hendelTime();
		m_window.clear();
		for (auto& shape : m_gameStaticObjects)
			shape->draw(m_window);
		for (auto& shape : m_bombsList)
		{
			shape->draw(m_window);
			shape->bombHandle();
		}
		for (auto& shape : m_gameObjects)
			if (shape->getIsAlive())
				shape->draw(m_window);
		m_gameObjects[m_robotIndex]->draw(m_window);
		Sleep(10); 
		moveObjects();
		eventHandler();
		if (m_state != NORMAL)
			break;
		
		printInfo(" ");
		m_window.display();
		
	}
	handleStateChange();
}



void Controller::printInfo(char * add_string)
{
	sf::Font font;
	char string[150];
	

	sprintf(string, "Points: %d \nLife: %d \nStage: %d\nbombs: %d \ntime: %.1f\n%s",
		m_points, m_life, m_stage, m_numOfBombs, m_time, add_string);
	font.loadFromFile("Gabriola.TTF");
	std::string str(string);
	sf::Text txt(str, font, 10);
	txt.setFillColor(sf::Color::Yellow);
	txt.setOutlineThickness(20);
	txt.setOutlineColor(sf::Color::Black);
	txt.setStyle(sf::Text::Bold);
	txt.setCharacterSize(30);
	txt.setPosition((float)m_screenBoundryMax.x + 50, (float)100);
	m_window.draw(txt);
}


void Controller::moveObjects()
{
	sf::Vector2f rbotLocation;
	rbotLocation = m_gameObjects[m_robotIndex]->getPosition();
	for (auto& shape : m_gameObjects)
	{
		shape->move(m_robotMove, m_screenBoundryMin, m_screenBoundryMax, rbotLocation);
		if ((m_state = shape->getState()) != NORMAL)
			return;
	}
}


void Controller::handleStateChange()
{
	if (m_state == ROBOT_FOUND_DOOR || m_state == GAME_OVER)
	{
		m_window.close();
	}
}

unsigned int Controller::getState()
{
	return m_state;
}

void Controller::setPoints(unsigned int totalPoints)
{
m_points = totalPoints;
}

void Controller::setLife(unsigned int lifeLeft)
{
	m_life = lifeLeft;
}

void Controller::setBombs(unsigned int bombs)
{
	m_numOfBombs = bombs;
}

void Controller::setTime(float time)
{
	m_time = time;
}



void Controller::setNumOfScreens(unsigned int screens)
{
	m_numOfScreens = screens;
}

void Controller::keyPressedHandler(const sf::Event& event)
{
	sf::Vector2f v{ 0,0 };
	switch (event.key.code)
	{
	case sf::Keyboard::Right:
		m_robotMove = { 5,0 };
		break;
	case sf::Keyboard::Left:
		m_robotMove = { -5 ,0 };
		break;
	case sf::Keyboard::Up:
		m_robotMove = { 0 , -5 };
		break;
	case sf::Keyboard::Down:
		m_robotMove = { 0 , 5 };
		break;
	case sf::Keyboard::Space:
		m_robotMove = { 0 , 0 };
		break;
	case sf::Keyboard::B:
		if (m_numOfBombs > 0)
		{
			m_robotMove = { 0 , 0 };
			m_bombsList.push_back(std::make_unique<Bomb,
				const sf::Vector2f&,
				const sf::Vector2f&,
				std::vector<sf::Texture>&,
				const unsigned int>
				({ RECT_SIZE, RECT_SIZE }, m_gameObjects[m_robotIndex]->getPosition(),
					m_textures, VBOMB));
			m_numOfBombs--;
		}
		break;
	case sf::Keyboard::D:
		resetRobot();
		if (m_state == GAME_OVER)
			return;
		restart();
		printInfo("You abandon\nthe game\nStarts over");
		m_window.display();
		Sleep(3000);
		break;
	default:
		break;
	}
}

void Controller::collideHandler()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{

		//-------------------guard killed robot--------------------------

		if (i != m_ghostIndex && m_gameObjects[m_robotIndex]->collideHandler(*m_gameObjects[i]) &&
			m_gameObjects[i]->getIsAlive() == true && i != m_robotIndex)
		{
			resetRobot();
			if (m_state == GAME_OVER)
				return;
		}
	

		if (i == m_ghostIndex && m_gameObjects[m_robotIndex]->collideHandler(*m_gameObjects[i]))
		{
			
			if (rand() % 34 == 0)
			{
				m_bombsList.push_back(std::make_unique<Ghostbomb,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int>
					({ RECT_SIZE, RECT_SIZE }, m_gameObjects[m_robotIndex]->getPosition(),
						m_textures, VGHOSTBOMB));
			}
			
		}
			

		//-----------------bomb killed gurad/robot/rock/presentrock ----------------------

		for (int l = 0; l < m_bombsList.size(); l++)
		{
			if (i != m_robotIndex && i != m_ghostIndex && m_bombsList[l]->getType() == VBOMB)
			{
				if (m_gameObjects[i]->collideHandlerBomb(*m_bombsList[l]) &&
					m_bombsList[l]->getState() == DURING_EXPLODED)
				{
					m_gameObjects[i]->disable();
					m_points += (5 * m_numOfGuards);
				}
			}

			if (m_gameObjects[m_robotIndex]->collideHandlerBomb(*m_bombsList[l]) &&
				m_bombsList[l]->getState() == DURING_EXPLODED)
			{
				resetRobot();
				if (m_state == GAME_OVER)
					return;
			}
				

			for ( int k=0 ;  k < m_gameStaticObjects.size() ; k++)
				if (m_gameStaticObjects[k]->getType() == VROCK &&
					m_bombsList[l]->collideHandlerBomb(*m_gameStaticObjects[k])&&
					m_bombsList[l]->getState() == DURING_EXPLODED &&
					m_bombsList[l]->getType() == VBOMB )
						m_gameStaticObjects[k]->disable();

			for (int k = 0; k < m_gameStaticObjects.size(); k++)
				if (m_gameStaticObjects[k]->getType() == VPRESENETROCK &&
					m_bombsList[l]->collideHandlerBomb(*m_gameStaticObjects[k]) &&
					m_bombsList[l]->getState() == DURING_EXPLODED &&
					m_bombsList[l]->getType() == VBOMB)
				{
					//m_gameStaticObjects[k]->disable();
					m_gameStaticObjects[k]->updatePicture(VPRESENT);
				}

		}


		for (int j = 0 ; j < m_gameStaticObjects.size(); j++)
		{
			if (m_gameObjects[i]->collideHandlerStatic(*m_gameStaticObjects[j]))
			{
				if (i != m_robotIndex)
					m_gameObjects[i]->m_guardCollide = true;
				m_gameObjects[i]->moveRevert();
			}
			m_state = m_gameObjects[i]->getState();
			if (m_state == ROBOT_FOUND_PRESENT)
			{
				m_gameStaticObjects[j]->disable();
				m_gameStaticObjects[j]->changeActive();
				m_state = NORMAL;
				m_gameObjects[i]->changeState();
				m_numOfBombs++;
				return;
			}

		}
	}

}

void Controller::resetRobot()
{
	m_life--;
	if (m_life == 0)
	{
		m_state = GAME_OVER;
		printInfo("GAME OVER");
		m_window.display();
		Sleep(3000);
		return;
	}
	m_gameObjects[m_robotIndex]->setToDefault();
	m_robotMove = { 0, 0 };
	for (int k = 0; k < m_gameObjects.size(); k++)
	{
		if (k != m_robotIndex)
		{
			m_gameObjects[k]->setToDefault();
			m_gameObjects[k]->restartPosition();
		}
	}
}



void Controller::hendelTime()
{
	m_t = m_clock.getElapsedTime();
	m_time = m_t.asSeconds();
	m_time = m_time * -1 + m_board.getTime();
	if (m_time <= 0)
	{
		restart();
		m_time = 0;
		m_life--; 
		printInfo("Time Ended \nRestarting\n");
		m_window.display();
		Sleep(3000);
		m_clock.restart();
	}

}

void Controller::restart()
{
	for (auto& shape : m_gameObjects)
		shape->setToDefault();
	for (auto& shape : m_gameStaticObjects)
		shape->backToDefault();
	m_time = m_board.getTime();
	m_robotMove = { 0 , 0 };
}


unsigned int Controller::getPoints()
{
	return m_points;
}
unsigned int Controller::getLife()
{
	return m_life;
}

unsigned int Controller::getNumOfBombs()
{
	return m_numOfBombs;
}

float Controller::getTime()
{
	return m_time;
}