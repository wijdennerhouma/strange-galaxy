#include"spaceship.h"
#include"globals.h"
spaceship::spaceship() :
	gravity(10),
	flap_speed(250),
	
	anim_counter(0),
	texture_switch(1),
	should_fly(false)
{ 
	textures[0].loadFromFile("alien_down.png");
	textures[1].loadFromFile("alien_down.png");

	spaceship_sprite.setTexture(textures[0]);
	spaceship_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	resetspaceshipPosition();
}


void spaceship::update(sf::Time&dt)
{
	if (spaceship_sprite.getGlobalBounds().top < 495 && should_fly)
	{
		if (anim_counter == 5)
		{
			spaceship_sprite.setTexture(textures[texture_switch]);
			if (texture_switch) texture_switch = 0;
			else texture_switch = 1;
			anim_counter = 0;
		}
		anim_counter++;

		velocity_y += gravity * dt.asSeconds();
		spaceship_sprite.move(0, velocity_y);


		if (spaceship_sprite.getGlobalBounds().top < 0)
			spaceship_sprite.setPosition(100,0);
	}

}

void spaceship::flapspaceship(sf::Time &dt)
{
	velocity_y = -flap_speed * dt.asSeconds();
}

float spaceship::getRightBound()
{
	return spaceship_sprite.getGlobalBounds().left + spaceship_sprite.getGlobalBounds().width;
}

void spaceship::resetspaceshipPosition()
{
	spaceship_sprite.setPosition(100,200);
	velocity_y = 0;

}

void spaceship::setShouldFly(bool should_fly)
{
	this->should_fly = should_fly;
}


