#include "mob.h"

mob::mob()
{
	position = { 100,100 };
	healthBar.setSize({31, 3});
	healthBar.setFillColor({255,0,0,150});
	healthBar.setOutlineThickness(1);
	healthBar.setOutlineColor({0,0,0,150});
}

void mob::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box);
	if (health < max_health)
	{
		target.draw(healthBar);
	}
}

void mob::setPosition(sf::Vector2f pos)
{
	position = pos;
}

void mob::attack()
{
	power = 0;
}

void mob::update(sf::Time& deltaTime, sf::Vector2f player_pos, world* world)
{
	bool isBlockRight = (world->getBlockTypeOn({ position.x + 15, position.y - 4 }) > 0 || world->getBlockTypeOn({ position.x + 15, position.y - 20 }) > 0 || world->getBlockTypeOn({ position.x + 15, position.y - 36 }) > 0);
	bool isBlockLeft  = (world->getBlockTypeOn({ position.x - 15, position.y - 4 }) > 0 || world->getBlockTypeOn({ position.x - 15, position.y - 20 }) > 0 || world->getBlockTypeOn({ position.x - 15, position.y - 36 }) > 0);
	bool isBlockBelow = (world->getBlockTypeOn({ position.x - 10, position.y + 2 }) > 0 || world->getBlockTypeOn({ position.x + 10, position.y + 2 })  > 0 || world->getBlockTypeOn({ position.x, position.y + 2 }) > 0);
	bool isBlockAbove = (world->getBlockTypeOn({ position.x - 10, position.y - 50 }) > 0 || world->getBlockTypeOn({ position.x + 10, position.y - 50 }) > 0);


	if (position.x > player_pos.x + 10)
	{
		//move left
		if (isBlockLeft && !inAir)
		{
			speed.y -= jump_speed;
			inAir = true;
		}
		if (!isBlockLeft)
		{
			box.setScale({ -1,1 });
			if (speed.x > -max_speed)
			{
				speed.x -= 4;
			}
			if (speed.x > 0)
			{
				speed.x -= 40;
			}
		}
	}
	else if (position.x < player_pos.x - 10)
	{
		//move right
		if (isBlockRight && !inAir)
		{
			speed.y -= jump_speed;
			inAir = true;
		}
		if (!isBlockRight)
		{
			box.setScale({ 1,1 });
			if (speed.x < max_speed)
			{
				speed.x += 4;
			}
			if (speed.x < 0)
			{
				speed.x += 40;
			}
		}
	}
	else
	{
		speed.x = 0;
		if (!inAir)
		{
			speed.y -= jump_speed;
			inAir = true;
		}
	}
	if ((isBlockLeft && speed.x < 0) || (isBlockRight && speed.x > 0))
	{
		speed.x = 0;
	}

	if (!isBlockBelow)
	{
		inAir = true;
	}
	if (isBlockAbove && speed.y < 0)
	{
		speed.y = 0;
	}
	if (inAir && speed.y < 740)
	{
		speed.y += 1000 * deltaTime.asMicroseconds() / 1'000'000.0f;
	}
	if (inAir && isBlockBelow && speed.y >= 0)
	{
		speed.y = 0;
		inAir = false;
	}

	position.x += speed.x * deltaTime.asMicroseconds() / 1'000'000.0f;
	position.y += speed.y * deltaTime.asMicroseconds() / 1'000'000.0f;

	animate(deltaTime);

	box.setPosition(position);

	healthBar.setSize({ (health * 1.0f / max_health * 1.0f) * 31.0f , 3 });
	healthBar.setPosition({ position.x - 15, position.y - 55 });

	power += 20 * deltaTime.asMicroseconds() / 1'000'000.0f;
}

bool mob::readyToAttack()
{
	if (power > min_power_to_attack)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void mob::knockback(float force, bool dir)
{
	if (dir)
	{
		speed.x += force;
		position.x += 2;
	}
	else
	{
		speed.x -= force;
		position.x -= 2;
	}
}

void mob::hit(int dmg)
{
	health -= dmg;
}

bool mob::alive()
{
	if (health >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::Vector2f mob::getPosition()
{
	return position;
}

//----------------------------------------------

zombie::zombie()
{
	health = 200;
	max_health = 200;
	damage = 20;
	min_power_to_attack = 50;
	max_speed = 70;
	jump_speed = 300;
	texture.loadFromFile("Textures/zombie.png", sf::IntRect{ 0,0,0,0 });
	box.setTexture(texture);
	box.setTextureRect({ 0,0,31,47 });
	box.setOrigin({ 16,46 });
}

void mob::animate(sf::Time& deltaTime)
{
	if (abs(speed.x) == 0)
	{
		animation_step = 0;
	}
	else
	{
		animation_step += abs(speed.x) * deltaTime.asMicroseconds() / 1'000'000.0f;
	}
	
	if (animation_step == 0)
	{
		box.setTextureRect({ 0,0,31,47 });
	}
	else if (animation_step > 0 && animation_step <= 10)
	{
		box.setTextureRect({ 31,0,31,47 });
	}
	else if (animation_step > 10 && animation_step <= 20)
	{
		box.setTextureRect({ 62,0,31,47 });
	}
	else
	{
		box.setTextureRect({ 93,0,31,47 });
	}

	if (animation_step > 30)
	{
		animation_step = 0;
	}
}