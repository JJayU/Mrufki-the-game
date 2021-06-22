#include "player.h"

player::player()
{
	if (!texture.loadFromFile("Textures/player_texture.png"))
	{
		std::cout << "Could not load player texture\n";
	}
	player_sprite.setTexture(texture);
	player_sprite.setOrigin({16,46});
}

void player::setPosition(sf::Vector2f newPos)
{
	position = newPos;
}

void player::update(sf::Time& deltaTime, world* world)
{
	bool isBlockBelow = (world->getBlockTypeOn({ position.x - 10, position.y + 2 })  >  0 || world->getBlockTypeOn({ position.x + 10, position.y + 2 })  >  0 || world->getBlockTypeOn({ position.x, position.y + 2 })       >  0);
	bool isBlockAbove = (world->getBlockTypeOn({ position.x - 10, position.y - 50 }) >  0 || world->getBlockTypeOn({ position.x + 10, position.y - 50 }) >  0);
	bool isBlockRight = (world->getBlockTypeOn({ position.x + 15, position.y - 4 })  >  0 || world->getBlockTypeOn({ position.x + 15, position.y - 20 }) >  0 || world->getBlockTypeOn({ position.x + 15, position.y - 36 }) >  0);
	bool isBlockLeft  = (world->getBlockTypeOn({ position.x - 15, position.y - 4 })  >  0 || world->getBlockTypeOn({ position.x - 15, position.y - 20 }) >  0 || world->getBlockTypeOn({ position.x - 15, position.y - 36 }) >  0);
	bool stairsRight  = (world->getBlockTypeOn({ position.x + 15, position.y - 4 })  >  0 && world->getBlockTypeOn({ position.x + 15, position.y - 20 }) == 0 && world->getBlockTypeOn({ position.x + 15, position.y - 36 }) == 0);
	bool stairsLeft   = (world->getBlockTypeOn({ position.x - 15, position.y - 4 })  >  0 && world->getBlockTypeOn({ position.x - 15, position.y - 20 }) == 0 && world->getBlockTypeOn({ position.x - 15, position.y - 36 }) == 0);


	//horizontal moves
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isBlockLeft)
	{
		player_sprite.setScale({ -1,1 });
		if (currentSpeed.x > -MAX_SPEED)
		{
			currentSpeed.x -= 4;
		}
		if (currentSpeed.x > 0)
		{
			currentSpeed.x -= 40;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isBlockRight)
	{
		player_sprite.setScale({ 1,1 });
		if (currentSpeed.x < MAX_SPEED)
		{
			currentSpeed.x += 4;
		}
		if (currentSpeed.x < 0)
		{
			currentSpeed.x += 40;
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (stairsLeft || stairsRight))
	{
		currentSpeed.y -= 30;
	}
	else if (isBlockRight || isBlockLeft && !stairsRight)
	{
		currentSpeed.x = 0;
	}
	else
	{
		if (abs(currentSpeed.x) >= 0)
		{
			if (abs(currentSpeed.x) < 10)
			{
				currentSpeed.x = 0;
			}
			else if (currentSpeed.x > 0)
			{
				currentSpeed.x -= 1000 * deltaTime.asMicroseconds() / 1'000'000.0f;
			}
			else if (currentSpeed.x < 0)
			{
				currentSpeed.x += 1000 * deltaTime.asMicroseconds() / 1'000'000.0f;
			}
		}
	}

	//verical moves
	if (!isBlockBelow)
	{
		inAir = true;
	}
	if (isBlockAbove && currentSpeed.y < 0)
	{
		currentSpeed.y = 0;
	}
	if (inAir && currentSpeed.y < MAX_SPEED*2)
	{
		currentSpeed.y += 1000 * deltaTime.asMicroseconds() / 1'000'000.0f;
	}
	if (inAir && isBlockBelow && currentSpeed.y >= 0)
	{
		currentSpeed.y = 0;
		//position.y = position.y + 16 - (int)position.y % 16;
		inAir = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !inAir)
	{
		currentSpeed.y = -500;
		inAir = true;
	}

	position.x += currentSpeed.x * deltaTime.asMicroseconds() / 1'000'000.0f;
	position.y += currentSpeed.y * deltaTime.asMicroseconds() / 1'000'000.0f;

	player_sprite.setPosition(position);

	//std::cout << 1'000'000.0f / deltaTime.asMicroseconds() << "\n";   //FPS
}

sf::Vector2f player::getEyesPos()
{
	float x = position.x;
	float y = position.y - 32;

	return { x, y };
}

void player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(player_sprite);
}
