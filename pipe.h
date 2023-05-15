#pragma once
#include<SFML/Graphics.hpp>
class pipe
{
public:
	pipe(int);
	sf::Sprite sprite_up, sprite_down ,sprite_mi;
	static void loadTextures();
	void update(sf::Time&);
	float getRightBound();

private:
	static sf::Texture texture_down, texture_up;
	static int pipe_distance, move_speed;

};
