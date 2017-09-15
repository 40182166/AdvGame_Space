#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.hpp"

class MainMenu : public Menu
{
public:
	virtual void showMenu(sf::RenderWindow& window);
	virtual void InputHandler(sf::RenderWindow &window);
	void showHighScore(sf::RenderWindow &window);

	static bool isPlaying;

private:
	std::vector<sf::Sprite> buttons;
	std::vector<sf::Texture> buttonsTexture;
	const int NUM_BUTTONS = 3;
	int indexSelection = 0;
	

};


