#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.hpp"

class PauseMenu : public Menu
{
public:
	virtual void showMenu(sf::RenderWindow& window);
	virtual void InputHandler(sf::RenderWindow &window);
	void saveScore(sf::RenderWindow &window, int score);

	static bool isPlayingFromPause;
	static bool isSaved;

private:
	std::vector<sf::Sprite> buttonsPause;
	std::vector<sf::Texture> buttonsTexturePause;
	const int NUM_BUTTONS_Pause = 2;
	int indexSelectionPause = 0;

	std::vector<sf::Sprite> buttonsSave;
	std::vector<sf::Texture> buttonsTextureSave;
	const int NUM_BUTTONS_Save = 2;
	int indexSelectionSave = 0;


};