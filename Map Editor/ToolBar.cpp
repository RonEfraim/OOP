#include "ToolBar.h"
#include "GraphicsManager.h"


void ToolBar::build(sf::RenderWindow &m_window)
{
	//toolbar shape horizonal (3)
	static sf::RectangleShape shape3(sf::Vector2f(LEN, WID));
	//toolbar shape vertical (4)
	static sf::RectangleShape shape4(sf::Vector2f(WID, LEN*SHAPES));
	//where to start draw toolbar hor
	shape3.setPosition(sf::Vector2f{ m_initialPos });
	//where to start draw toolbar ver
	shape4.setPosition(sf::Vector2f{ m_initialPos });

	//draw hor lines
	for (int i = 0; i <= SHAPES; i++)
	{
		m_window.draw(shape3);
		//distance between lines
		shape3.move(0, LEN);		
	}

	//draw ver lines
	for (int i = 0; i < 2; i++)
	{
		m_window.draw(shape4);
		//distance between lines
		shape4.move(LEN, 0);
	}


	for (int i = 0; i < SHAPES; i++)
	{
		m_objects[i]->draw(m_window);
	}
}

bool ToolBar::in_toolbar(sf::Vector2i pos)
{
	sf::Vector2i topLeft = { LEN, LEN*5 };
	sf::Vector2i bottomRight = { LEN*2 , LEN*11 };

	//if in range of toolbar
	if (pos.x > topLeft.x && 
		pos.y > topLeft.y &&
		pos.x < bottomRight.x &&
		pos.y < bottomRight.y)
		return true;

	return false;
}

int ToolBar::clickedOn(const sf::Vector2i & pos)
{	
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i]->contains(sf::Vector2f{ pos }))
		return i;
	}
	return -1;
}


ToolBar::ToolBar() :m_initialPos({ LEN ,LEN * 5 })
{
	m_objects.resize(SHAPES);
	m_char_vector.assign(SHAPES, ' ');
	
	m_char_vector[0] = '/';
	m_char_vector[1] = '!';
	m_char_vector[2] = '#';
	m_char_vector[3] = '@';
	m_char_vector[4] = 'D';
	m_char_vector[5] = 'C';
	m_char_vector[6] = 'S';
	m_char_vector[7] = 'T';

	for(int i =0; i<SHAPES; i++)
		m_objects[i] = new Objects(GraphicsManager::get_instance().getTexture(i), m_char_vector[i], sf::Vector2f{(float)m_initialPos.x + 3,(float)m_initialPos.y + 3 + LEN * i });
	
}

ToolBar::~ToolBar()
{
}

