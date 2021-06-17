#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "world.h"

class game : public sf::Drawable
{
public:
	game();
	void update(sf::Time& deltaTime);

private:
	player player; 
	sf::View mainView;
	world world;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

