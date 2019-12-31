#pragma once

#include <SFML/Graphics.hpp>



class StaticObject
{
public:
	StaticObject(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~StaticObject();
	StaticObject(std::vector<sf::Texture>& textures);
	bool isActive();
	void backToDefault();
	void disable();
	void draw(sf::RenderWindow& renderWindow);
	bool isCollide(const sf::FloatRect& rect) const;
	unsigned int m_objectType;
	void changeActive();
	void updatePicture(unsigned int index);
	void changeSize(const sf::Vector2f& size);
	sf::Vector2f getPos();
	unsigned int getType();
	

protected:
	sf::RectangleShape m_rectangle;
	
	
	

private:
	bool m_active;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	const sf::Vector2f m_defaultPosition = { 400 ,400 };
	sf::Vector2f m_originalPosition;
	unsigned int m_type;
	
};

/*
BaseObject() = default;
virtual ~BaseObject() = default;
virtual void draw(sf::RenderWindow& renderWindow) const = 0;
*/