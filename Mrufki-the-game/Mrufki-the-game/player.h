#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once

#define MAX_SPEED 320

class player : public sf::Drawable
{
public:
	void setPosition(sf::Vector2f newPos);
	void update(sf::Time& deltaTime);
	sf::Vector2f getEyesPos();
private:
	sf::Vector2f position = { 0, 256 };
	sf::Vector2f currentSpeed = { 0,0 };
	bool inAir = false;

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

