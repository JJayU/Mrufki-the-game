#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.h"
#include "world.h"
#include "mob.h"

#define MOB_CAP 10

class game : public sf::Drawable
{
public:
	game();
	void update(sf::Time* deltaTime);
	void updateOnEvent(sf::Event* eventToReact, sf::Vector2f mouse_position);
	world world;
	

private:
	player player;
	sf::View mainView;
	sf::Font fpsFont;
	sf::Text fpsDisplay;
	int loops = 0;
	float current_time = 360;			// 0 - 6:00, 60 - 7:00...
	
	std::string clock();

	sf::Music music;
	sf::SoundBuffer sound_buffer1;
	sf::SoundBuffer sound_buffer2;
	sf::SoundBuffer sound_buffer3;
	sf::Sound attack_sound;
	sf::Sound block_placed_sound;
	sf::Sound block_destroyed_sound;

	bool game_state = true;				// false if the game is over

	mob* mobs[MOB_CAP];

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

