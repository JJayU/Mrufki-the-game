#include "block.h"

/*
	Blocks ID list:
	0 - air
	1 - dirt
	2 - grass
	3 - stone
	4 - wooden planks
	5 - wall
	6 - cobblestone
	7 - smooth stone
	8 - wood
	9 - glass
*/

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
	texture.loadFromFile("Textures/textures.png", getTextureCoords(ID_));
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
