#include "Bomberman.h"
#include <memory>
#include "Controller.h"



Bomberman::Bomberman() :
	m_window(sf::VideoMode(600, 300), "Bomberman"),
	m_textures(3)
{
	m_totalPoints = 0;
	m_numOfScreens = 0;
	m_activeScreen = 0;
	m_lifeLeft = 0;
	m_endgame.setSize({ 210 , 100 });
	m_start.setSize({ 210 , 100 });
	sf::Vector2f endPos;
	sf::Vector2f startPos;
	m_window.setVisible(false);
	m_font.loadFromFile("Gabriola.TTF");
	if (!m_textures[VEND].loadFromFile("endgame.png")
		|| !m_textures[VSTART].loadFromFile("start.png")
		)
	{
		m_window.close();
		return;
	}

	endPos = { 175,125 };
	startPos = { 425,125 };

	//----------------endgame-------------------------------

	m_endgame.setPosition(endPos);
	m_endgame.setTexture(&m_textures[VEND]);
	m_endgame.setOrigin(m_endgame.getLocalBounds().width / 2,
		m_endgame.getLocalBounds().height / 2);
	
	//----------------startgame------------------------------

	m_start.setPosition(startPos);
	m_start.setTexture(&m_textures[VSTART]);
	m_start.setOrigin(m_start.getLocalBounds().width / 2,
		m_start.getLocalBounds().height / 2);
}


Bomberman::~Bomberman()
{
}


void Bomberman::addController(char *fileName)
{
	m_controllers.push_back(std::make_unique<Controller,
		char * & , unsigned int & >(fileName, m_numOfScreens));
	m_numOfScreens++;
}


bool Bomberman::run()
{
	switch (hendelEndStartGame()) {
	case VEND:
	case VCLOSE:
		return false;
	case VSTART:
		break;
	};
	
	while (m_activeScreen < m_numOfScreens)
	{
		m_controllers[m_activeScreen]->run();
		unsigned int state = m_controllers[m_activeScreen]->getState();
		if (state == ROBOT_FOUND_DOOR)
			if (moveToNextScreen() == GAME_OVER)
				break;
		if (state == GAME_OVER)
			break;
	}
	switch (hendelEndStartGame()) {
	case VEND:
	case VCLOSE:
		return false;
	case VSTART:
		return true;
	};
	return false;
}

int Bomberman::hendelEndStartGame()
{
	sf::Event event{};
	m_window.setVisible(true);
	while (m_window.isOpen())
	{
		m_window.clear();
		m_window.draw(m_endgame);
		m_window.draw(m_start);
		m_window.display();
		m_window.waitEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			return VCLOSE;
			break;
		case sf::Event::MouseButtonPressed:
			if (MousePressedHandler(event) == VSTART)
			{
				
				m_window.setVisible(false);
				return VSTART;
			}
			if (MousePressedHandler(event) == VEND)
			{
				m_window.close();
				return VEND;
			}
			break;
		default:
			break;
		}
		
	}

}

int Bomberman::MousePressedHandler(sf::Event event)
{
	const auto coords = m_window.mapPixelToCoords
	({ event.mouseButton.x, event.mouseButton.y });

	if (m_endgame.getGlobalBounds().contains(coords) == true)
		return VEND;

	if (m_start.getGlobalBounds().contains(coords) == true)
		return VSTART;
		
}




unsigned int Bomberman::moveToNextScreen()
{
	saveDataToNextScrean();

	// active screen is the next one
	m_activeScreen++;
	if (m_activeScreen >= m_numOfScreens)
		return GAME_OVER;

	

	// copy the data to the next screen
	m_controllers[m_activeScreen]->setPoints(m_totalPoints);
	m_controllers[m_activeScreen]->setLife(m_lifeLeft);
	m_controllers[m_activeScreen]->setBombs(m_bombsLeft);
	m_controllers[m_activeScreen]->setTime(m_timeLeft);
	m_controllers[m_activeScreen]->setNumOfScreens(m_numOfScreens);
}

void Bomberman::saveDataToNextScrean()
{
	m_totalPoints = m_controllers[m_activeScreen]->getPoints();
	m_lifeLeft = m_controllers[m_activeScreen]->getLife();
	m_timeLeft = m_controllers[m_activeScreen]->getTime();
	m_bombsLeft = m_controllers[m_activeScreen]->getNumOfBombs();
}

