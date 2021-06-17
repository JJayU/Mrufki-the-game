#include "chunk.h"

chunk::chunk(sf::Vector2f position)
{
	position_ = position;

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			blocks[j][i] = new block(0, { position.x + 16 * j, position.y + 16 * i });
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
