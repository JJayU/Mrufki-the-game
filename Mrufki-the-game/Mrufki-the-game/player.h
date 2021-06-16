#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once

class player
{
public:
	void draw(sf::RenderWindow *target);
	void setPosition(sf::Vector2f newPos);
	void update();
	sf::Vector2f getEyesPos();
private:
	sf::Vector2f position = { 0,0 };
	sf::Vector2f currentSpeed = { 0,0 };
};

