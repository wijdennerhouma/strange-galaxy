#pragma once
#include<SFML/Graphics.hpp>

class spaceship
{
private:
	sf::Texture textures[2];
	const int gravity;
	const int flap_speed;
	float velocity_y;
	int anim_counter, texture_switch;
	bool should_fly;
public:
	sf::Sprite spaceship_sprite;
	spaceship();
	void setShouldFly(bool);
	void flapspaceship(sf::Time&);
	void resetspaceshipPosition();
	void update(sf::Time&);
	float getRightBound();




};
