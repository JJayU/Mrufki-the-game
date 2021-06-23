#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "world.h"

class mob : public sf::Drawable
{
public:
	mob();
	void update(sf::Time& deltaTime, sf::Vector2f player_pos, world* world);
	bool readyToAttack();
	void attack();
	void knockback(float force, bool dir);
	void hit(int dmg);
	bool alive();
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

protected:
	int health = 100;
	sf::Sprite box;
	sf::RectangleShape healthBar;
	sf::Texture texture;
	sf::Vector2f position;
	sf::Vector2f speed = { 0,0 };
	bool rotation;
	bool inAir = false;

	int max_speed;
	int max_health;
	int jump_speed;
	int damage;
	float power = 0;
	int min_power_to_attack;
	void animate(sf::Time& deltaTime);
	float animation_step = 0;

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class zombie : public mob
{
public:
	zombie();
};