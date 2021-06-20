#include "chunk.h"

chunk::chunk(sf::Vector2f position)
{
	position_ = position;

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			blocks[j][i] = new block(1, { position.x + 16 * j, position.y + 16 * i });
		}
	}
}

void chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			target.draw(*blocks[j][i]);
		}
	}
}

int chunk::getBlockTypeOn(sf::Vector2f position)
{
	int x = ( (int)position.x / 16 ) % 8;
	int y = ( (int)position.y / 16 ) % 8;

	return blocks[x][y]->getID();
}

void chunk::setBlock(sf::Vector2f position, int id)
{
	int x = ((int)position.x / 16) % 8;
	int y = ((int)position.y / 16) % 8;

	blocks[x][y]->setID(id);
}