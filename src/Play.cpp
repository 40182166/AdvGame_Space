#include "Play.hpp"
#include "Player.hpp"

Player player;

Play::Play()
{
}


Play::~Play()
{
}

void Play::StartGame(sf::RenderWindow& window)
{
	
	player.CreateShip(5, window);
}


