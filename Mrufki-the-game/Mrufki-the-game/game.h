#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"

class game
{
public:
	game();
	void update();
	void draw(sf::RenderWindow* target);
	sf::View mainView;
private:
	player player;
};

