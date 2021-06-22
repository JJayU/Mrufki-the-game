#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "world.h"

#define DISPLAY_FPS true

class game : public sf::Drawable
{
public:
	game();
	void update(sf::Time* deltaTime);
	void updateOnEvent(sf::Event* eventToReact, sf::Vector2f mouse_position);
	world world;
	

private:
	player player;
	sf::View mainView;
	sf::Font fpsFont;
	sf::Text fpsDisplay;
	int loops = 0;
	

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

