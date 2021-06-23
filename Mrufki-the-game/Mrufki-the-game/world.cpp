#include "world.h"

world::world()
{
	//Initialise blocks
	for (int i = 0; i < WORLD_SIZE/2; i++)
	{
		for (int j = 0; j < WORLD_SIZE; j++)
		{
			chunks[j][i] = new chunk({ 128.0f * j, 128.0f * i });
		}
	}

	//World generator
	srand(time(NULL));
	std::vector<int> surface = perlinNoise(WORLD_SIZE * 8, 1);

	//Surface
	for (int i = 0; i < WORLD_SIZE * 8; i++)
	{
		sf::Vector2f pos = { (float)i * 16.0f, (float)surface[i] * 16.0f + 160.0f};
		for (int j = pos.y; j < WORLD_SIZE * 8 * 16; j += 16)
		{
			if (j - pos.y < 16)
			{
				setBlock({ pos.x, pos.y + j - pos.y }, 2);
			}
			else if (j - pos.y < 128)
			{
				setBlock({ pos.x, pos.y + j - pos.y }, 1);
			}
			else
			{
				setBlock({ pos.x, pos.y + j - pos.y }, 3);
			}
		}
	}
	
	//Wall
	for (int i = 0; i < WORLD_SIZE * 8; i++)
	{
		for (int j = 0; j < WORLD_SIZE * 8 / 2; j++)
		{
			if (i == 0 || i == WORLD_SIZE * 8 - 1 || j == 0 || j == WORLD_SIZE * 8 / 2 - 1)
			{
				setBlock({ (float)i * 16.0f + 1.0f, (float)j * 16.0f + 1.0f }, 5);
			}
		}
	}

}

world::~world()
{
	for (int i = 0; i < WORLD_SIZE / 2; i++)
	{
		for (int j = 0; j < WORLD_SIZE; j++)
		{
			delete chunks[j][i];
		}
	}
}

int world::getWorldSize()
{
	return WORLD_SIZE * 8 * 16;
}

void world::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::View tview = target.getView();
	sf::FloatRect viewdim = tview.getViewport();

	int left = (tview.getCenter().x - 320 > 0 ? tview.getCenter().x - 320 : 0);
	int top = (tview.getCenter().y - 180 > 0 ? tview.getCenter().y - 180 : 0);

	int right = (left + 640) / 128 + 1< WORLD_SIZE ? (left + 640) / 128 + 1 : WORLD_SIZE;
	int bottom = (top + 480) / 128 + 1 < WORLD_SIZE/2 ? (top + 480) / 128 + 1 : WORLD_SIZE/2;

	left = left / 128;
	top = top / 128;

	for (size_t i = top; i < bottom; i++)
	{
		for (size_t j = left; j < right; j++)
		{
			target.draw(*chunks[j][i]);
		}
	}
}

int world::getBlockTypeOn(sf::Vector2f position)
{
	int chunkX = position.x / 128;
	int chunkY = position.y / 128;

	if (position.x > 0 && chunkX < WORLD_SIZE && position.y > 0 && chunkY < WORLD_SIZE / 2)
	{
		return chunks[chunkX][chunkY]->getBlockTypeOn(position);
	}
	else
	{
		return -1;
	}
}

void world::setBlock(sf::Vector2f position, int id)
{
	int chunkX = position.x / 128.0;
	int chunkY = position.y / 128.0;

	if (position.x > 0 && chunkX < WORLD_SIZE && position.y > 0 && chunkY < WORLD_SIZE / 2)
	{
		chunks[chunkX][chunkY]->setBlock(position, id);
	}
}

std::vector<int> world::perlinNoise(int length, int seed)
{
	std::vector<int> pass1 = noiseFunction(length, WORLD_SIZE / 4, WORLD_SIZE * 8 / 4);

	return pass1;
}

std::vector<int> world::noiseFunction(int length, int frequency, int amplitude)
{
	std::vector<int> result;
	std::vector<int> points;

	int wavelength = length / frequency;

	for (size_t i = 0; i <= length; i += wavelength)
	{
		points.push_back(rand() % amplitude);
	}

	for (size_t i = 0; i < length; i ++)
	{
		float ti = i;
		float twl = wavelength;
		float x = ti / wavelength - i / wavelength;
		result.push_back(interpolate(points[i / wavelength], points[(i / wavelength) + 1], x));
	}

	return result;
}

float world::interpolate(int a, int b, float x)
{
	float f = (1 - cos(x * 3.141592)) * 0.5;

	return a * (1 - f) + b * f;
}