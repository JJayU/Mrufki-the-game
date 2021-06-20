#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.h"

#pragma once

#define MAX_SPEED 320

class player : public sf::Drawable
{
public:
	player();
	void setPosition(sf::Vector2f newPos);
	void update(sf::Time& deltaTime, world* world);
	sf::Vector2f getEyesPos();
private:
	sf::Texture texture;
	sf::Sprite player_sprite;
	sf::Vector2f position = { 0, 256 };
	sf::Vector2f currentSpeed = { 0,0 };
	bool inAir = false;
	bool rotation = true;		//right - true, left - false

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

