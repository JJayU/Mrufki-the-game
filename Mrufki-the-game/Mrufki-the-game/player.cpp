#include "player.h"

void player::setPosition(sf::Vector2f newPos)
{
	position = newPos;
}

void player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		position.y--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position.y++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		position.x--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position.x++;
	}
}

sf::Vector2f player::getEyesPos()
{
	float x = position.x - 16;
	float y = position.y - 32;

	return { x, y };
}

void player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape playerBox;
	playerBox.setPosition(position);
	playerBox.move(-16, -48);
	playerBox.setSize(sf::Vector2f(32, 48));
	playerBox.setFillColor(sf::Color::Black);

	target.draw(playerBox);
}
