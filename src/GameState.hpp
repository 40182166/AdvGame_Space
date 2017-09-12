#pragma once

class GameState
{
public:
	GameState();
	~GameState();

	static void initialize();
	//static void setState(String setState);
	static bool isFullScreen;

	
	static void menu();
	static void play();
	/*
	static void pause();
	static void win();
	static void lose();*/

	enum States
	{
		s_menu,
		s_play/*,
		s_pause,
		s_win,
		s_lose*/
	};

	static void running();
	static enum States changeState(GameState::States);
};

