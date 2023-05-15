#include"game.h"
#include"globals.h"
#include<sstream>
#include<fstream>


game::game(sf::RenderWindow& window) :win(window),
is_enter_pressed(false),
run_game(true),
start_monitoring(false),
pipe_counter(71),
pipe_spawn_time(70),
score(0)

{
	music.openFromFile("MainMusic.ogg");
	music.setVolume(30);
	music.play();

	music1.openFromFile("over.ogg");
	music1.setVolume(30);
	


	win.setFramerateLimit(60);
	bg_texture.loadFromFile("back.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	bg_sprite.setPosition(0.f, -0.f);


	ground_texture.loadFromFile("ground.png");
	ground_sprite1.setTexture(ground_texture);
	ground_sprite2.setTexture(ground_texture);


	ground_sprite1.setScale(SCALE_FACTOR, SCALE_FACTOR);
	ground_sprite2.setScale(SCALE_FACTOR, SCALE_FACTOR);

	ground_sprite1.setPosition(0,495);
	ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width,495);

	font.loadFromFile("arial.ttf");
	
	score_text.setFont(font);
	score_text.setCharacterSize(24);
	score_text.setFillColor(sf::Color::Black);
	score_text.setPosition(15, 15);
	score_text.setString("score:0");


	over_texture.loadFromFile("game_over.png");
	over_sprite.setTexture(over_texture);
	over_sprite.setScale(1.1,1);
	restart_text.setPosition(800, 400);

	
	



	pipe::loadTextures();
}
void game::doProcessing(sf::Time& dt)
{
	
	if(is_enter_pressed)
	{
		moveGround(dt);


		if(pipe_counter>pipe_spawn_time)
		{
			pipes.push_back(pipe(dist(rd)));
			pipe_counter = 0;
		}

		pipe_counter++;

		for (int i = 0; i < pipes.size(); i++)
		{
			pipes[i].update(dt);
			if (pipes[i].getRightBound() < 0)
			{
				pipes.erase(pipes.begin() + i);
			}
		}

		checkCollisions();
		checkScore();
		
	}
	spaceship.update(dt);
}

void game::startGameLoop()
{
	sf::Clock clock;
	//game loop
	while (win.isOpen())
	{
		
		sf::Time dt = clock.restart();
		sf::Event event;
		//event loop
		while (win.pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Down)
			{
				music.setVolume(music.getVolume() - 30);//annuler la music
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				music.setVolume(music.getVolume() + 30);//ajouter la music
			}
			if (event.type == sf::Event::Closed)
			{
				win.close();

			}
			if (event.type == sf::Event::KeyPressed && run_game)
			{
				if (event.key.code == sf::Keyboard::Enter && !is_enter_pressed)
				{
					is_enter_pressed = true;
					spaceship.setShouldFly(true);
				}
				if (event.key.code == sf::Keyboard::Space && is_enter_pressed)
				{
					spaceship.flapspaceship(dt);
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !run_game)
			{   if(event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left &&!run_game)

				restartGame();
			    music.play();
			}
		}
		doProcessing(dt);		

		
			
		
	
		draw();
		
		
		//display th window
		win.display();
		
	}
}

void game::checkCollisions()
{
	if (pipes.size() > 0)
	{
		if (pipes[0].sprite_down.getGlobalBounds().intersects(spaceship.spaceship_sprite.getGlobalBounds()) ||
			pipes[0].sprite_up.getGlobalBounds().intersects(spaceship.spaceship_sprite.getGlobalBounds()) ||
			spaceship.spaceship_sprite.getGlobalBounds().top >= 540)
		{
			is_enter_pressed = false;
			run_game = false;
			music.stop();
			music1.play();
			
		}
	}

	
}

void game::checkScore()
{
	if (pipes.size() > 0)
	{
		if (!start_monitoring)
		{
			if (spaceship.spaceship_sprite.getGlobalBounds().left < pipes[0].sprite_down.getGlobalBounds().left && spaceship.getRightBound() < pipes[0].getRightBound())
			{
				start_monitoring = true;
				
			}
		}
		else
		{
			if (spaceship.spaceship_sprite.getGlobalBounds().left > pipes[0].getRightBound())
			{
				score++;
				score_text.setString("score:" + toString(score));
				start_monitoring = false;
			}
		}
	}

	
}

void game::draw()
{
	win.draw(bg_sprite);
	for (pipe& pipe : pipes)
	{
		win.draw(pipe.sprite_down);
		win.draw(pipe.sprite_up);
		
	}
	win.draw(ground_sprite1);
	win.draw(ground_sprite2);
	win.draw(spaceship.spaceship_sprite);
	win.draw(score_text);
	
	if (!run_game)
	{
		win.draw(over_sprite);
		
	}
}
void game::moveGround(sf::Time& dt)
{
	ground_sprite1.move(-move_speed * dt.asSeconds(), 0.f);
	ground_sprite2.move(-move_speed * dt.asSeconds(), 0.f);

	if (ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width < 0)
	{
		ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width, 495);

	}
	if (ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width < 0)
	{
		ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width, 495);

	}

	

}

void game::restartGame()
{
	spaceship.resetspaceshipPosition();
	spaceship.setShouldFly(false);
	run_game = true;
	is_enter_pressed = false;
	pipe_counter = 71;
	pipes.clear();
	score = 0;
	score_text.setString("Score:0");
}


std::string game::toString(int num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}