#include "player.h"

void player::setPosition(sf::Vector2f newPos)
{
	position = newPos;
}

void player::update(sf::Time& deltaTime)
{
	//horizontal moves
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (currentSpeed.x > -MAX_SPEED)
		{
			currentSpeed.x -= 4;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (currentSpeed.x < MAX_SPEED)
		{
			currentSpeed.x += 4;
		}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !inAir)
	{
		currentSpeed.y = -500;
		inAir = true;
	}
	if (inAir && position.y < 256)
	{
		currentSpeed.y += 1000 * deltaTime.asMicroseconds() / 1'000'000.0f;
	}
	if (position.y > 256)
	{
		currentSpeed.y = 0;
		position.y = 256;
		inAir = false;
	}

	position.x += currentSpeed.x * deltaTime.asMicroseconds() / 1'000'000.0f;
	position.y += currentSpeed.y * deltaTime.asMicroseconds() / 1'000'000.0f;

	std::cout << 1'000'000.0f / deltaTime.asMicroseconds() << "\n";   //FPS
}

sf::Vector2f player::getEyesPos()
{
	float x = position.x - 16;
	float y = position.y - 32;

	return { x, y };
}

void player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Texture texture;
	if (!texture.loadFromFile("Textures/player.png"))
	{
		std::cout << "Could not load player texture\n";
	}

	sf::RectangleShape playerBox;
	playerBox.setTexture(&texture);
	playerBox.setPosition(position);
	playerBox.move(-16, -48);
	playerBox.setSize(sf::Vector2f(32, 48));

	target.draw(playerBox);
}
