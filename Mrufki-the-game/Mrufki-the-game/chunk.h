#pragma once
#include "block.h"

class chunk : public sf::Drawable
{
public:
	chunk(sf::Vector2f position);
	~chunk();
	sf::Vector2f position_ = { 0,0 };
	int getBlockTypeOn(sf::Vector2f position);
	void setBlock(sf::Vector2f position, int id);

private:
	block* blocks[8][8];

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

