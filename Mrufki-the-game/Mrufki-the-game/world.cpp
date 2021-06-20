#include "world.h"

world::world()
{
	for (int i = 0; i < WORLD_SIZE/2; i++)
	{
		for (int j = 0; j < WORLD_SIZE; j++)
		{
			chunks[j][i] = new chunk({ 128.0f * j, 128.0f * i });
		}
	}
}

void world::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::View tview = target.getView();
	sf::FloatRect viewdim = tview.getViewport();

	int left = (tview.getCenter().x - 320 > 0 ? tview.getCenter().x - 320 : 0);
	int top = (tview.getCenter().y - 180 > 0 ? tview.getCenter().y - 180 : 0);

	int right = (left + 640) / 128 + 1< WORLD_SIZE ? (left + 640) / 128 + 1 : WORLD_SIZE;
	int bottom = (top + 480) / 128 + 1 < WORLD_SIZE/2 ? (top + 480) / 128 + 1 : WORLD_SIZE/2;

	left = left / 128;
	top = top / 128;

	for (size_t i = top; i < bottom; i++)
	{
		for (size_t j = left; j < right; j++)
		{
			target.draw(*chunks[j][i]);
		}
	}
}

int world::getBlockTypeOn(sf::Vector2f position)
{
	int chunkX = position.x / 128;
	int chunkY = position.y / 128;

	if (position.x > 0 && chunkX < WORLD_SIZE && position.y > 0 && chunkY < WORLD_SIZE / 2)
	{
		return chunks[chunkX][chunkY]->getBlockTypeOn(position);
	}
	else
	{
		return -1;
	}
}

void world::setBlock(sf::Vector2f position, int id)
{
	int chunkX = position.x / 128;
	int chunkY = position.y / 128;

	if (position.x > 0 && chunkX < WORLD_SIZE && position.y > 0 && chunkY < WORLD_SIZE / 2)
	{
		chunks[chunkX][chunkY]->setBlock(position, id);
	}
}