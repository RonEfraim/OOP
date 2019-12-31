#include "Objects.h"

Objects::Objects(const sf::Texture * t, const char & s,const sf::Vector2f pos) :m_texture(t), m_symbol(s),m_pos(pos)
{
}

bool Objects::contains(sf::Vector2f pos)
{
	sf::RectangleShape r({ 30.f,30.f });
	r.setPosition(m_pos);
	return r.getGlobalBounds().contains(pos);
	
}

void Objects::draw(sf::RenderWindow & window, sf::Vector2f pos)
{
	sf::Sprite s(*m_texture);
	if (pos.x == -1 && pos.y == -1) //no position send
		s.setPosition(m_pos);
	else //position send
		s.setPosition(pos);
	window.draw(s);
}

char Objects::getChar() const
{
	return m_symbol;
}

Objects::~Objects()
{
}
