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

	int left = (tview.getCenter().x - viewdim.width > 0 ? tview.getCenter().x - viewdim.width : 0);
	int top = (tview.getCenter().y - viewdim.height > 0 ? tview.getCenter().y - viewdim.height : 0);

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