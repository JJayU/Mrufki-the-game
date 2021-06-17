#pragma once
#include "block.h"

class chunk : public sf::Drawable
{
public:
	chunk(sf::Vector2f position);
	sf::Vector2f position_ = { 0,0 };

private:
	block* blocks[8][8];

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

