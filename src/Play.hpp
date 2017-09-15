#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include "Play.hpp"
#include "Player.hpp"

class Play
{
public:
	Play();
	~Play();

	void StartGame(sf::RenderWindow& window, Player thisPlayer);


};

