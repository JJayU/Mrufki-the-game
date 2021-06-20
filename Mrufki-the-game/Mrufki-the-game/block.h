#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class block : public sf::Drawable
{
public:
	block(unsigned int id, sf::Vector2f position);
	sf::Vector2f position_ = { 0,0 };
	
	unsigned int getID();
	void setID(unsigned int id);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateTexture();
	sf::Texture texture;
	sf::Sprite block_sprite;
	unsigned int ID_;
};

