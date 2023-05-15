#pragma once
#include<SFML/Graphics.hpp>

#include<SFML/Audio.hpp>
#include"spaceship.h"
#include"pipe.h"
#include<vector>
#include<random>

class game {
public:
	game(sf::RenderWindow& window);
	sf::RenderWindow& win;
	sf::Music music;
	sf::Music music1;

	void startGameLoop();
private:
	sf::Texture bg_texture,ground_texture,over_texture;
	sf::Sprite bg_sprite,ground_sprite1,ground_sprite2,over_sprite;
	spaceship spaceship;
	bool is_enter_pressed, run_game,start_monitoring;
	const int move_speed = 270;
	void draw();
	void moveGround(sf::Time&);
	void doProcessing(sf::Time &dt);
	void checkCollisions();
	void restartGame();
	void checkScore();
    std::string toString(int);
	int pipe_counter, pipe_spawn_time,score;
	std::vector<pipe> pipes;
	std::random_device rd;
	std::uniform_int_distribution<int> dist{ 250,550 };

	sf::Font font;
	sf::Text restart_text,score_text;


};