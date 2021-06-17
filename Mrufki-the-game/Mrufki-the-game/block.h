#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class block : public sf::Drawable
{
public:
	block(unsigned int id, sf::Vector2f position);

	unsigned int ID_;
	sf::Vector2f position_ = { 0,0 };
	sf::Texture texture;
private:
	// Odziedziczono za poœrednictwem elementu Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateTexture();
	sf::Sprite block_sprite;
};

