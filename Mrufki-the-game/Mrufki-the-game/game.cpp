#include "game.h"

game::game()
{
	mainView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	mainView.setCenter(sf::Vector2f(0, 0));
	mainView.setSize(sf::Vector2f(640, 360));
	player.setPosition({ 160,40 });

	fpsFont.loadFromFile("Textures/Roboto-Light.ttf");
	fpsDisplay.setFont(fpsFont);
	fpsDisplay.setString("FPS: 0");
	fpsDisplay.setCharacterSize(10);
	fpsDisplay.setFillColor(sf::Color::White);
}

void game::update(sf::Time* deltaTime)
{
	player.update(*deltaTime, &world);
	mainView.setCenter(player.getEyesPos());

	sf::Vector2f fpsPosition = { player.getEyesPos().x - 320, player.getEyesPos().y - 180 };
	fpsDisplay.setPosition(fpsPosition);
	if (loops++ > 20)
	{
		loops = 0;
		int fps = 1'000'000.0f / deltaTime->asMicroseconds();
		fpsDisplay.setString("FPS: " + std::to_string(fps));
	}
}

void game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(mainView);
	target.draw(world);
	target.draw(player);
	target.draw(fpsDisplay);
	target.draw(player.inventory);
}

void game::updateOnEvent(sf::Event* eventToReact, sf::Vector2f mouse_position)
{
	if (eventToReact->type == sf::Event::MouseButtonPressed)
	{
		if (sqrt((mouse_position.x - player.getEyesPos().x) * (mouse_position.x - player.getEyesPos().x) + (mouse_position.y - player.getEyesPos().y) * (mouse_position.y - player.getEyesPos().y)) < 160)
		{
			if (eventToReact->mouseButton.button == sf::Mouse::Right)
			{
				// Placing blocks
				if (world.getBlockTypeOn(mouse_position) == 0)
				{
					if (player.inventory.selectedItem() < 90 && player.inventory.selectedItem() != 0)
					{
						std::cout << player.inventory.selectedItem() << "\n";
						world.setBlock(mouse_position, player.inventory.selectedItem());
					}
				}
			}
			if (eventToReact->mouseButton.button == sf::Mouse::Left)
			{
				// Mine
				if (player.inventory.selectedItem() == 98 && world.getBlockTypeOn(mouse_position) != 5)
				{
					world.setBlock(mouse_position, 0);
				}

				// Fight
				if (player.inventory.selectedItem() == 99)
				{
					//fighting
				}
			}
		}
	}

	// Inventory scrolling
	if (eventToReact->type == sf::Event::MouseWheelScrolled)
	{
		if (eventToReact->mouseWheelScroll.delta > 0)
		{
			player.inventory.scrollLeft();
		}
		else
		{
			player.inventory.scrollRight();
		}
	}
}
