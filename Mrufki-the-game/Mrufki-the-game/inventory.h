#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "getTextureCoords.h"

class inventory : public sf::Drawable
{
public:
	inventory();
	void scrollRight();
	void scrollLeft();
	void selectItem(int slot);
	int selectedItem();

private:
	int toolbar[9] = {0,0,0,0,0,0,0,0,0};
	sf::Texture toolbar_textures[9];
	int current_slot = 0;

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

