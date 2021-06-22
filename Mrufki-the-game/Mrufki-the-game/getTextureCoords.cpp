#include "getTextureCoords.h"

sf::IntRect getTextureCoords(int id)
{
	switch (id)
	{
	case 0:						// air
		return { 0,0,16,16 };
		break;
	case 1:						// dirt
		return { 16,0,16,16 };
		break;
	case 2:						// grass
		return { 32,0,16,16 };
		break;
	case 3:						// stone
		return { 48,0,16,16 };
		break;
	case 4:						// wooden planks
		return { 64,0,16,16 };
		break;
	case 5:						// bricks (wall)
		return { 80,0,16,16 };
		break;
	case 6:						// cobblestone
		return { 96,0,16,16 };
		break;
	case 7:						// smooth stone
		return { 112,0,16,16 };
		break;
	case 8:						// wood
		return { 128,0,16,16 };
		break;
	case 9:						// glass
		return { 144,0,16,16 };
		break;
	case 99:					// sword
		return { 128,144,16,16 };
		break;
	case 98:					// pickaxe
		return { 144,144,16,16 };
		break;
	default:
		break;
	}
}