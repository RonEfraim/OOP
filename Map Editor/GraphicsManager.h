#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utilities.h"

class GraphicsManager
{
public:
	~GraphicsManager();
	static GraphicsManager& get_instance();
	const sf::Texture* getTexture(const int i) const;
	const sf::Texture* getTexture(const char i) const;

private:
	GraphicsManager();
	void loadPictures();
	GraphicsManager(const GraphicsManager&) = delete;
	GraphicsManager& operator=(GraphicsManager&) = delete;
	
	std::vector<sf::Texture> m_textures;
};



