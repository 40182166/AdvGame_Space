#include "GameState.hpp"
#include "MainMenu.hpp"
#include "Play.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

using namespace sf;

RenderWindow GameState::window;
GameState::States GameState::currentState = s_uninitialized;
bool GameState::isFullScreen = true;
MainMenu main;
Play game; 
Player _player;

Texture texturetry;
Sprite playertry;
float thresholdBoundtry = 50.0f;

GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::Start()
{
	if (currentState != s_uninitialized)
		return;
	window.create(VideoMode(1280, 720), "Cat Invaders", sf::Style::Close);
	currentState = GameState::s_menu;
	while (!isExiting())
	{
		initialize();
	}
	window.close();
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

	switch (currentState)
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




void GameState::menu()
{
	
	main.showMenu(window);
}

void GameState::play()
{
	game.StartGame(window);
}


bool GameState::isExiting()
{
	if (currentState == GameState::s_exit)
		return true;
	else
		return false;
}


