#pragma once
#include <SFML/Graphics/Rect.hpp>

class MyRectangle;
class MyText;
class MySprite;

namespace sf {
	class Color;
	class RenderWindow;
}

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;
	virtual void click(const sf::Vector2f& coords) = 0;
	virtual void draw(sf::RenderWindow& renderWindow) const = 0;
	virtual void move(const sf::Vector2f& vector2f, bool isControlPressed) = 0;
	virtual bool scaleHandler(const sf::Vector2f& coords, float scale) = 0;
	virtual void setToDefault() = 0;
	virtual void uncollideHandler() = 0;

	virtual void rotate(int angle, bool isControlPressed) = 0;

	virtual bool isCollide(const sf::FloatRect& rect) const = 0;

	virtual bool collideHandler(Object& historicalObject) = 0;
	virtual bool collideHandler(MySprite& sprite) = 0;
	virtual bool collideHandler(const MyRectangle& rectangle) = 0;
	virtual bool collideHandler(const MyText& text) = 0;
};

