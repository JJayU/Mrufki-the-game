#include "block.h"

block::block(unsigned int id, sf::Vector2f position)
{
	ID_ = id;
	position_ = position;
	updateTexture();
	block_sprite.setTexture(texture);
	block_sprite.setPosition(position_);
}

void block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(block_sprite);
}

void block::updateTexture()
{
	switch (ID_)
	{
	case 0:
		texture.loadFromFile("Textures/textures.png", sf::IntRect(0, 0, 16, 16));
		break;
	case 1:
		texture.loadFromFile("Textures/textures.png", sf::IntRect(16, 0, 16, 16));
		break;
	default:
		break;
	}
}

unsigned int block::getID()
{
	return ID_;
}

void block::setID(unsigned int id)
{
	ID_ = id;
	updateTexture();
}
