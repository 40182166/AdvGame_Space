#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

class Play
{
public:
	Play();
	~Play();

	static void StartGame(sf::RenderWindow& window);

};

