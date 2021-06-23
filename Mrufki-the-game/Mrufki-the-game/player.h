#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.h"
#include "inventory.h"
#include "getTextureCoords.h"

#pragma once

#define MAX_SPEED 320
#define MAX_HEALTH 200

class player : public sf::Drawable
{
public:
	player();
	void setPosition(sf::Vector2f newPos);
	void update(sf::Time& deltaTime, world* world);
	sf::Vector2f getEyesPos();
	inventory inventory;
	bool getRotation();
	void setRotation(bool rot);
	void hit(int damage);
	bool isAlive();
	bool readyToAttack();
	void attack();

private:
	sf::Texture texture;
	sf::Texture items;
	sf::Sprite player_sprite;
	sf::Sprite item_in_hand;
	sf::Vector2f position;
	sf::Vector2f currentSpeed = { 0,0 };
	sf::RectangleShape healthBar;
	bool inAir = false;
	bool rotation = true;		//right - true, left - false
	float health = MAX_HEALTH / 2;
	float power = 0;
	void animate(sf::Time& deltaTime);
	float animation_step = 0;

	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

