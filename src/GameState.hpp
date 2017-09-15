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
	static void DrawGameBoard();
	static void DrawGameStats();
	static int randomSpawn(int min, int max);
	static bool isJoysticConnected;
	static bool isplayerDead;


	static void menu();
	static void play();
	static void pause();
	static void toBeSaved();
	static void highScore();
	static void lose();

	enum States
	{
		s_uninitialized,
		s_menu,
		s_play,
		s_exit,
		s_pause,
		s_save,
		s_score,
		s_lose
	};
	static sf::RenderWindow window;
	static void running();
	static States currentState;
};

