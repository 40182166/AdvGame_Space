#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

using namespace sf;

class GameState
{
public:
	GameState();
	~GameState();

	static void initialize();
	static void Start();
	static bool isFullScreen;
	static bool isExiting();

	
	static void menu();
	static void play();
	/*
	static void pause();
	static void win();
	static void lose();*/

	enum States
	{
		s_uninitialized,
		s_menu,
		s_play,
		s_exit/*,
		s_pause,
		s_win,
		s_lose*/
	};
	static sf::RenderWindow window;
	static void running();
	static States currentState;
};

