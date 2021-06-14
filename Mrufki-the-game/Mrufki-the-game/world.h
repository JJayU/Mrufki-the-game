#pragma once
#include "block.h"
#include <vector>

class World
{
public:
	enum worldType {Small, Medium, Large};
	World(worldType wordltype);
protected:
	size_t mapsize_ = 16;
	std::vector<std::vector<Block>> map_;
};

World::World(worldType worldtype)
{
	switch (worldtype)
	{
	case World::Small:
		mapsize_ = 16;
		break;
	case World::Medium:
		mapsize_ = 32;
		break;
	case World::Large:
		mapsize_ = 64;
		break;
	default:
		break;
	}

	for (size_t i = 0; i < mapsize_ / 2; i++)
	{
		std::vector<Block> tChunkRow;
		for (size_t j = 0; j < mapsize_; j++)
		{
			Block block(1);
			tChunkRow.push_back(block);
		}
		map_.push_back(tChunkRow);
	}
}

