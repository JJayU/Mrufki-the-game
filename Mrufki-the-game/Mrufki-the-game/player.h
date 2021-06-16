#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once

class player : public sf::Drawable
{
public:
	void setPosition(sf::Vector2f newPos);
	void update();
	sf::Vector2f getEyesPos();
private:
	sf::Vector2f position = { 0,0 };
	sf::Vector2f currentSpeed = { 0,0 };

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

