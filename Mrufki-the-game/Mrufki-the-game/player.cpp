#include "player.h"

player::player()
{
	if (!texture.loadFromFile("Textures/player.png"))
	{
		std::cout << "Could not load player texture\n";
	}
	if (!items.loadFromFile("Textures/textures.png"))
	{
		std::cout << "Could not load items textures\n";
	}
	player_sprite.setTexture(texture);
	player_sprite.setOrigin({16,46});

	healthBar.setSize({ 100, 3 });
	healthBar.setFillColor({ 255,0,0,150 });
	healthBar.setOutlineThickness(1);
	healthBar.setOutlineColor({ 0,0,0,150 });

	item_in_hand.setTexture(items);
	item_in_hand.setOrigin({ 0,16 });
}

void player::setPosition(sf::Vector2f newPos)
{
	position = newPos;
}

void player::setRotation(bool rot)
{
	rotation = rot;
}

void player::update(sf::Time& deltaTime, world* world)
{
	bool isBlockBelow = (world->getBlockTypeOn({ position.x - 10, position.y + 2 })  >  0 || world->getBlockTypeOn({ position.x + 10, position.y + 2 })  >  0 || world->getBlockTypeOn({ position.x, position.y + 2 })       >  0);
	bool isBlockAbove = (world->getBlockTypeOn({ position.x - 10, position.y - 50})  >  0 || world->getBlockTypeOn({ position.x + 10, position.y - 50 }) >  0 || world->getBlockTypeOn({ position.x, position.y - 50})       >  0);
	bool isBlockRight = (world->getBlockTypeOn({ position.x + 15, position.y - 4 })  >  0 || world->getBlockTypeOn({ position.x + 15, position.y - 20 }) >  0 || world->getBlockTypeOn({ position.x + 15, position.y - 36 }) >  0);
	bool isBlockLeft  = (world->getBlockTypeOn({ position.x - 15, position.y - 4 })  >  0 || world->getBlockTypeOn({ position.x - 15, position.y - 20 }) >  0 || world->getBlockTypeOn({ position.x - 15, position.y - 36 }) >  0);
	bool stairsRight  = (world->getBlockTypeOn({ position.x + 15 + abs(currentSpeed.x / 10), position.y - 4 })  >  0 && world->getBlockTypeOn({ position.x + 15 + abs(currentSpeed.x / 10), position.y - 20 }) == 0 && world->getBlockTypeOn({ position.x + 15 + abs(currentSpeed.x / 10), position.y - 36 }) == 0);
	bool stairsLeft   = (world->getBlockTypeOn({ position.x - 15 - abs(currentSpeed.x / 10), position.y - 4 })  >  0 && world->getBlockTypeOn({ position.x - 15 - abs(currentSpeed.x / 10), position.y - 20 }) == 0 && world->getBlockTypeOn({ position.x - 15 - abs(currentSpeed.x / 10), position.y - 36 }) == 0);


	//horizontal moves
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isBlockLeft)
	{
		rotation = false;
		if (currentSpeed.x > -MAX_SPEED)
		{
			currentSpeed.x -= 4;
		}
		if (currentSpeed.x > 0)
		{
			currentSpeed.x -= 40;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isBlockRight)
	{
		rotation = true;
		if (currentSpeed.x < MAX_SPEED)
		{
			currentSpeed.x += 4;
		}
		if (currentSpeed.x < 0)
		{
			currentSpeed.x += 40;
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (stairsLeft || stairsRight))
	{
		currentSpeed.y -= 30;
	}
	else if ((isBlockRight && !stairsRight && currentSpeed.x > 0) || (isBlockLeft&& !stairsLeft && currentSpeed.x < 0))
	{
		currentSpeed.x = 0;
	}
	else
	{
		if (abs(currentSpeed.x) >= 0)
		{
			if (abs(currentSpeed.x) < 10)
			{
				currentSpeed.x = 0;
			}
			else if (currentSpeed.x > 0)
			{
				currentSpeed.x -= 1000 * deltaTime.asMicroseconds() / 1'000'000.0f;
			}
			else if (currentSpeed.x < 0)
			{
				currentSpeed.x += 1000 * deltaTime.asMicroseconds() / 1'000'000.0f;
			}
		}
	}

	//verical moves
	if (!isBlockBelow)
	{
		inAir = true;
	}
	if (isBlockAbove && currentSpeed.y < 0)
	{
		currentSpeed.y = 0;
	}
	if (inAir && currentSpeed.y < MAX_SPEED*2)
	{
		currentSpeed.y += 1000 * deltaTime.asMicroseconds() / 1'000'000.0f;
	}
	if (inAir && isBlockBelow && currentSpeed.y >= 0)
	{
		currentSpeed.y = 0;
		inAir = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !inAir && !isBlockAbove)
	{
		currentSpeed.y = -500;
		inAir = true;
	}

	position.x += currentSpeed.x * deltaTime.asMicroseconds() / 1'000'000.0f;
	position.y += currentSpeed.y * deltaTime.asMicroseconds() / 1'000'000.0f;

	player_sprite.setPosition(position);

	if (health < MAX_HEALTH)
	{
		health += 5 * deltaTime.asMicroseconds() / 1'000'000.0f;
	}

	healthBar.setSize({ (health * 1.0f / MAX_HEALTH * 1.0f) * 200.0f , 3 });
	healthBar.setPosition({ position.x - 100, position.y + 120 });

	if (rotation)
	{
		player_sprite.setScale({ 1,1 });
		item_in_hand.setScale({ 1,1 });
	}
	else
	{
		player_sprite.setScale({ -1,1 });
		item_in_hand.setScale({ -1,1 });
	}

	power += 10 * deltaTime.asMicroseconds() / 1'000'000.0f;

	animate(deltaTime);

	
	if (inventory.selectedItem() > 90)
	{
		item_in_hand.setTextureRect(getTextureCoords(inventory.selectedItem()));
	}
	else
	{
		item_in_hand.setTextureRect(getTextureCoords(0));
	}

	item_in_hand.setPosition({ position.x + 6, position.y - 12});
}

sf::Vector2f player::getEyesPos()
{
	float x = position.x;
	float y = position.y - 32;

	return { x, y };
}

void player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(player_sprite);
	target.draw(item_in_hand);
	target.draw(healthBar);
}

void player::hit(int damage)
{
	health -= damage;
}

bool player::isAlive()
{
	if (health > 0)
	{
		return true;
	}
	return false;
}

bool player::getRotation()
{
	return rotation;
}

bool player::readyToAttack()
{
	if (power > 5)
	{
		return true;
	}
	return false;
}

void player::attack()
{
	power = 0;
}

void player::animate(sf::Time& deltaTime)
{
	if (abs(currentSpeed.x) == 0)
	{
		animation_step = 0;
	}
	else
	{
		animation_step += abs(currentSpeed.x) * deltaTime.asMicroseconds() / 1'000'000.0f;
	}

	if (animation_step == 0)
	{
		player_sprite.setTextureRect({ 0,0,31,47 });
	}
	else if (animation_step > 0 && animation_step <= 10)
	{
		player_sprite.setTextureRect({ 31,0,31,47 });
	}
	else if (animation_step > 10 && animation_step <= 20)
	{
		player_sprite.setTextureRect({ 62,0,31,47 });
	}
	else
	{
		player_sprite.setTextureRect({ 93,0,31,47 });
	}

	if (animation_step > 30)
	{
		animation_step = 0;
	}
}