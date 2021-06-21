#pragma once
#include "chunk.h"
#include <vector>
#include <time.h>

#define WORLD_SIZE 16

class world : public sf::Drawable
{
public:
	world();
	int getBlockTypeOn(sf::Vector2f position);
	void setBlock(sf::Vector2f position, int id);

private:
	chunk* chunks[WORLD_SIZE][WORLD_SIZE/2];
	std::vector<int> perlinNoise(int size, int seed);
	std::vector<int> noiseFunction(int length, int frequency, int amplitude);
	float interpolate(int a, int b, float x);

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

