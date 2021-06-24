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

	for (size_t i = 0; i < MOB_CAP; i++)
	{
		mobs[i] = nullptr;
	}

	if (!music.openFromFile("Content/soundtrack.wav"))
	{
		std::cout << "Could not load music!\n";
	}
	music.play();
	music.setLoop(true);
	music.setVolume(30.0f);
	if (!sound_buffer1.loadFromFile("Content/attack.ogg"))
	{
		std::cout << "Could not load sounds!\n";
	}
	if (!sound_buffer2.loadFromFile("Content/block_placed.ogg"))
	{
		std::cout << "Could not load sounds!\n";
	}
	if (!sound_buffer3.loadFromFile("Content/block_destroyed.ogg"))
	{
		std::cout << "Could not load sounds!\n";
	}
	attack_sound.setBuffer(sound_buffer1);
	attack_sound.setVolume(20.0f);
	block_placed_sound.setBuffer(sound_buffer2);
	block_destroyed_sound.setBuffer(sound_buffer3);
}

void game::update(sf::Time* deltaTime)
{
	if (!player.isAlive())
	{
		game_state = false;
	}
	else
	{
		player.update(*deltaTime, &world);
		mainView.setCenter(player.getEyesPos());

		sf::Vector2f fpsPosition = { player.getEyesPos().x - 320, player.getEyesPos().y - 180 };
		fpsDisplay.setPosition(fpsPosition);
		if (loops++ > 20)
		{
			loops = 0;
			int fps = 1'000'000.0f / deltaTime->asMicroseconds();
			fpsDisplay.setString(clock() + "\nFPS: " + std::to_string(fps));
		}

		for (size_t i = 0; i < MOB_CAP; i++)
		{
			if (mobs[i] != NULL)
			{
				if (!mobs[i]->alive())
				{
					mobs[i] = nullptr;
					continue;
				}
				mobs[i]->update(*deltaTime, player.getEyesPos(), &world);

				float distance = sqrt(pow(player.getEyesPos().x - mobs[i]->getPosition().x, 2) + pow(player.getEyesPos().y + 20 - mobs[i]->getPosition().y, 2));
				if (distance < 20 && mobs[i]->readyToAttack())
				{
					player.hit(25);
					mobs[i]->attack();
				}
			}
			else
			{
				if (current_time > 960 && rand() % 10000 > 9990)
				{
					mobs[i] = new zombie;
					float tpos = 60 + rand() % (world.getWorldSize() - 120);
					mobs[i]->setPosition({ tpos, 70 });
				}
			}
		}

		current_time += 10 * deltaTime->asMicroseconds() / 1'000'000.0f;
		if (current_time > 1440)
		{
			current_time = 0;
		}
	}
}

void game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (game_state)
	{
		if (current_time > 960)
		{
			target.clear(sf::Color(50, 50, 150));
		}
		target.setView(mainView);
		target.draw(world);

		for (size_t i = 0; i < MOB_CAP; i++)
		{
			if (mobs[i] != NULL)
			{
				target.draw(*mobs[i]);
			}
		}

		target.draw(player);
		target.draw(fpsDisplay);
		target.draw(player.inventory);
	}
	else
	{
		target.clear(sf::Color::Black);
		sf::Text text;
		text.setFont(fpsFont);
		text.setString("Game over!\n\nPress ESCAPE to exit\n\nThank you for playing!");
		text.setCharacterSize(10);
		text.setFillColor(sf::Color::White);
		sf::View view = target.getView();
		sf::Vector2f tpos = view.getCenter();
		text.setPosition({tpos.x - 50,tpos.y - 50});

		target.draw(text);
	}
}

void game::updateOnEvent(sf::Event* eventToReact, sf::Vector2f mouse_position)
{
	if (game_state)
	{
		if (eventToReact->type == sf::Event::MouseButtonPressed)
		{
			if (sqrt((mouse_position.x - player.getEyesPos().x) * (mouse_position.x - player.getEyesPos().x) + (mouse_position.y - player.getEyesPos().y) * (mouse_position.y - player.getEyesPos().y)) < 160)
			{
				if (mouse_position.x < player.getEyesPos().x)
				{
					player.setRotation(false);
				}
				else
				{
					player.setRotation(true);
				}

				if (eventToReact->mouseButton.button == sf::Mouse::Right)
				{
					// Placing blocks
					if (world.getBlockTypeOn(mouse_position) == 0)
					{
						if (player.inventory.selectedItem() < 90 && player.inventory.selectedItem() != 0)
						{
							world.setBlock(mouse_position, player.inventory.selectedItem());
							block_placed_sound.play();
						}
					}
				}
				if (eventToReact->mouseButton.button == sf::Mouse::Left)
				{
					// Mine
					if (player.inventory.selectedItem() == 98 && world.getBlockTypeOn(mouse_position) != 5 && world.getBlockTypeOn(mouse_position) != 0)
					{
						block_destroyed_sound.play();
						world.setBlock(mouse_position, 0);
					}

					// Fight
					if (player.inventory.selectedItem() == 99 && player.readyToAttack())
					{
						attack_sound.play();
						player.attack();
						for (size_t i = 0; i < MOB_CAP; i++)
						{
							if (mobs[i] != NULL)
							{
								if (player.getEyesPos().x > mobs[i]->getPosition().x && player.getRotation() == false)
								{
									float distance = sqrt(pow(player.getEyesPos().x - mobs[i]->getPosition().x, 2) + pow(player.getEyesPos().y - mobs[i]->getPosition().y, 2));
									if (distance < 100)
									{
										mobs[i]->hit(30);
										mobs[i]->knockback(500, false);
									}
								}
								else if (player.getEyesPos().x < mobs[i]->getPosition().x && player.getRotation() == true)
								{
									float distance = sqrt(pow(player.getEyesPos().x - mobs[i]->getPosition().x, 2) + pow(player.getEyesPos().y - mobs[i]->getPosition().y, 2));
									if (distance < 100)
									{
										mobs[i]->hit(30);
										mobs[i]->knockback(500, true);
									}
								}
							}
						}
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
}

std::string game::clock()
{
	int hour = 6 + (int)current_time / 60;
	int minute = (int)current_time % 60;

	if (hour > 23)
	{
		hour -= 24;
	}

	std::string output = "Time: ";
	output += (hour >= 10 ? "" : "0");
	output += std::to_string(hour);
	output += ":";
	output += (minute >= 10 ? "" : "0");
	output += std::to_string(minute);

	return output;
}