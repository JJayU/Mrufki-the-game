#include "inventory.h"

inventory::inventory()
{
	toolbar[0] = 99; //sword
	toolbar[1] = 98; //pickaxe
	toolbar[2] = 1;  //dirt
	toolbar[3] = 2;  //grass
	toolbar[4] = 3;  //stone
	toolbar[5] = 4;  //wood
}

void inventory::scrollLeft()
{
	current_slot--;
	if (current_slot < 0)
	{
		current_slot = 8;
	}
}

void inventory::scrollRight()
{
	current_slot++;
	if (current_slot > 8)
	{
		current_slot = 0;
	}
}

int inventory::selectedItem()
{
	return toolbar[current_slot];
}

void inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rect;
	rect.setSize({ 20, 20 });
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1);
	sf::View view = target.getView();
	sf::Vector2f tpos = view.getCenter();

	for (int i = 0; i < 9; i++)
	{
		if (i == current_slot)
		{
			rect.setOutlineColor(sf::Color::White);
		}
		else
		{
			rect.setOutlineColor(sf::Color::Black);
		}
		rect.setPosition({ tpos.x + (i - 5) * 24 + 12, tpos.y + 158 });
		target.draw(rect);
	}
}
