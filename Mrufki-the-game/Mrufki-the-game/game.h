#pragma once
#include "world.h"

class Game
{
public:
	Game();
private:
	World* world;
};

Game::Game()
{
	world = new World(World::Small);
}

