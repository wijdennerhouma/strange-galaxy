#include"pipe.h"
#include"globals.h"
pipe::pipe(int y_pos)
{

	sprite_down.setTexture(texture_down);
	sprite_up.setTexture(texture_up);
	


	sprite_down.setScale(SCALE_FACTOR, SCALE_FACTOR);
	sprite_up.setScale(SCALE_FACTOR, SCALE_FACTOR);

	sprite_up.setPosition(WIN_WIDTH, y_pos);
	sprite_down.setPosition(WIN_WIDTH, y_pos-1 - pipe_distance-1 - sprite_up.getGlobalBounds().height);


}
void pipe::update(sf::Time& dt)
{
	sprite_up.move(-move_speed * dt.asSeconds(), -1.f);

	sprite_down.move(-move_speed * dt.asSeconds(), 0.f);

}
void pipe::loadTextures()
{
	texture_down.loadFromFile("pip_b.png");
	texture_up.loadFromFile("pip_r.png");
	
}
float pipe::getRightBound()
{
	return sprite_down.getGlobalBounds().left+sprite_down.getGlobalBounds().width;
}

sf::Texture pipe::texture_down,pipe::texture_up;
int pipe::pipe_distance = 260,pipe::move_speed = 300;
