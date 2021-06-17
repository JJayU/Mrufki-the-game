#pragma once
#include "chunk.h"

#define WORLD_SIZE 8

class world : public sf::Drawable
{
public:
	world();

private:
	chunk* chunks[WORLD_SIZE][WORLD_SIZE/2];

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

