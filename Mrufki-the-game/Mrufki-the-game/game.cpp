#include "game.h"

game::game()
{
	mainView.setCenter(sf::Vector2f(0, 0));
	mainView.setSize(sf::Vector2f(640, 360));
}

void game::update()
{
	player.update();
	mainView.setCenter(player.getEyesPos());
}

void game::draw(sf::RenderWindow* target)
{
	player.draw(target);
}