#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	m_textures.resize(SHAPES+1);
	loadPictures();
}

void GraphicsManager::loadPictures()
{
	const std::string pictureFolder("Images/");
	const std::string pictureType(".png");
	for (int i = 0; i < SHAPES+1; i++)
	{
		//convert to string
		std::string picture_path = pictureFolder + std::to_string(i) + pictureType;
		//insert to toolbar
		m_textures[i].loadFromFile(picture_path);
	}
}

GraphicsManager & GraphicsManager::get_instance()
{
	static GraphicsManager instance;

	return instance;
}

const sf::Texture * GraphicsManager::getTexture(const int i) const
{
	return &m_textures[i];
}

const sf::Texture * GraphicsManager::getTexture(const char c) const
{
	static std::vector<char> m_char_vector = { '/','!','#','@','D','C','S','T'};

	for (int i = 0; i < m_char_vector.size(); i++)
	{
		if (c == m_char_vector[i])
			return &m_textures[i];
	}
}

GraphicsManager::~GraphicsManager()
{
}
