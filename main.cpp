#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"globals.h"
#include"game.h"
#include<iostream>
int main() {
	sf::RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Strange galaxy");
	
	game game(win);
	game.startGameLoop();
	return 0;
 }