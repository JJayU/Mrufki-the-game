#include "game.h"

game::game()
{
	mainView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	mainView.setCenter(sf::Vector2f(0, 0));
	mainView.setSize(sf::Vector2f(640, 360));

	//generate world
	//plant trees
	//etc
}

void game::update(sf::Time* deltaTime)
{
	//std::cout << world.getBlockTypeOn(player.getEyesPos()) << "\n";
	player.update(*deltaTime, &world);
	mainView.setCenter(player.getEyesPos());
}

void game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(mainView);
	target.draw(world);
	target.draw(player);
}
