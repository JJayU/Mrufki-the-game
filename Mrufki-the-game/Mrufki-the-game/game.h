#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"

class game : public sf::Drawable
{
public:
	game();
	void update();
	sf::View mainView;
private:
	player player;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

