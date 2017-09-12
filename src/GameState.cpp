#include "GameState.hpp"
#include "MainMenu.hpp"
#include "Play.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

using namespace sf;
RenderWindow window(VideoMode(1280, 720), "Cat Invaders", sf::Style::Close);
bool GameState::isFullScreen = true;
MainMenu main;
Play game; 
Player playMe;

GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::initialize()
{
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::B:
					if (isFullScreen)
					{
						window.create(VideoMode(1280, 720), "Cat Invaders", sf::Style::Close);
						isFullScreen = false;
					}
					else
					{
						window.create(VideoMode(1280, 720), "Cat Invaders", sf::Style::Fullscreen);
						isFullScreen = true;
					}
					break;
				}
				break;

				case Event::Closed:
					window.close();
					break;
			}
		}
		
		window.clear();
		running();
		window.display();
	}
}


void GameState::running()
{

	switch (changeState(s_play))
	{
		case s_menu:
			menu();
			break;

		case s_play:
			play();
			break;

		default:
			break;
	}
}

GameState::States GameState::changeState(GameState::States state)
{
	return state;
}



void GameState::menu()
{
	
	main.showMenu(window);
}

void GameState::play()
{
	//game.StartGame(window);
	playMe.CreateShip(5, window);
}



