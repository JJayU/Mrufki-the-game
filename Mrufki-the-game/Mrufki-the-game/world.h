#pragma once
#include "chunk.h"

#define WORLD_SIZE 8

class world : public sf::Drawable
{
public:
	world();
	int getBlockTypeOn(sf::Vector2f position);
	void setBlock(sf::Vector2f position, int id);

private:
	chunk* chunks[WORLD_SIZE][WORLD_SIZE/2];

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

