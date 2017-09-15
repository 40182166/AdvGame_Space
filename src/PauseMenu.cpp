#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "PauseMenu.h"
#include "GameState.hpp"
#include "Player.hpp"
#include <fstream>
#include <ctime>

bool PauseMenu::isPlayingFromPause = false;
bool PauseMenu::isSaved = false;
std::ofstream scoreFile;


sf::Texture pauseBackgroundTexture;
sf::Sprite pauseBackground;

sf::Texture saveBackgroundTexture;
sf::Sprite saveBackground;

void PauseMenu::showMenu(sf::RenderWindow &window)
{

	pauseBackgroundTexture.loadFromFile("res/img/pause_background.jpg");
	sf::Vector2f targetSize(window.getSize().x, window.getSize().y);
	pauseBackground.setTexture(pauseBackgroundTexture);
	pauseBackground.setScale(
		targetSize.x / pauseBackground.getLocalBounds().width,
		targetSize.y / pauseBackground.getLocalBounds().height);

	window.draw(pauseBackground);

	sf::Text pausedTxt;
	sf::Font fontPaused;
	fontPaused.loadFromFile("res/img/agencyb.ttf");
	pausedTxt.setFont(fontPaused);
	pausedTxt.setCharacterSize(150);
	pausedTxt.setColor(sf::Color::White);
	pausedTxt.setStyle(sf::Text::Bold);
	pausedTxt.setString("Paused");

	sf::FloatRect textRect = pausedTxt.getLocalBounds();
	pausedTxt.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	pausedTxt.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 100.0f));

	window.draw(pausedTxt);
/**/
	sf::Texture p_menuVisual;
	sf::Sprite p_menuText;


	for (int i = 0; i < NUM_BUTTONS_Pause; i++)
	{
		buttonsPause.push_back(p_menuText);
		buttonsTexturePause.push_back(p_menuVisual);


	}

	buttonsTexturePause[0].loadFromFile("res/img/resume_off.png");
	buttonsTexturePause[1].loadFromFile("res/img/exit_off.png");


	for (int i = 0; i < NUM_BUTTONS_Pause; i++)
	{
		buttonsPause[i].setTexture(buttonsTexturePause[i]);
		sf::FloatRect optionsRect = buttonsPause[i].getLocalBounds();
		buttonsPause[i].setOrigin(optionsRect.left + optionsRect.width / 2.0f,
			optionsRect.top + optionsRect.height / 2.0f);

		buttonsPause[i].setPosition(window.getSize().x / 2.0f, 350.0f + i * 100.0f);
		window.draw(buttonsPause[i]);
	}

	InputHandler(window);

}

void PauseMenu::InputHandler(sf::RenderWindow & window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{

		if (GameState::isJoysticConnected)
		{
			if (Joystick::isButtonPressed(0, 5)) // Xbox RB
			{
				if (indexSelectionPause < 1)
				{
					indexSelectionPause++;
				}
			}
			else if (Joystick::isButtonPressed(0, 4))
			{
				if (indexSelectionPause > 0)
				{
					indexSelectionPause--;
				}
			}
		}

		switch (event.type)
		{

		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:

			switch (event.key.code)
			{
			case sf::Keyboard::S:
				if (indexSelectionPause < 1)
				{
					indexSelectionPause++;
				}
				break;

			case sf::Keyboard::W:
				if (indexSelectionPause > 0)
				{
					indexSelectionPause--;
				}
				break;
			}
			break;
		}
	}

	switch (indexSelectionPause)
	{
	case 0:
		buttonsTexturePause[indexSelectionPause].loadFromFile("res/img/resume_on.png");
		window.draw(buttonsPause[indexSelectionPause]);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Joystick::isButtonPressed(0, 1) && GameState::isJoysticConnected == true) {
			GameState::currentState = GameState::States::s_play;
			isSaved = false;
		}

		break;

	case 1:
		buttonsTexturePause[indexSelectionPause].loadFromFile("res/img/exit_on.png");
		window.draw(buttonsPause[indexSelectionPause]);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Joystick::isButtonPressed(0, 1) && GameState::isJoysticConnected == true) {
			isSaved = false;
			GameState::currentState = GameState::States::s_save;
		}
		break;

	default:
		break;
	}
}

void PauseMenu::saveScore(sf::RenderWindow & window, int score)
{

	//////////////////

	saveBackgroundTexture.loadFromFile("res/img/pause_background.jpg");
	sf::Vector2f targetSize(window.getSize().x, window.getSize().y);
	saveBackground.setTexture(saveBackgroundTexture);
	saveBackground.setScale(
		targetSize.x / saveBackground.getLocalBounds().width,
		targetSize.y / saveBackground.getLocalBounds().height);

	window.draw(saveBackground);

	sf::Text savedText;
	sf::Font fontSave;
	fontSave.loadFromFile("res/img/agencyb.ttf");
	savedText.setFont(fontSave);
	savedText.setCharacterSize(70);
	savedText.setColor(sf::Color::White);
	savedText.setStyle(sf::Text::Bold);
	savedText.setString("Do you want to save your score?");

	sf::FloatRect textRect = savedText.getLocalBounds();
	savedText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	savedText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 200.0f));

	window.draw(savedText);

	sf::Texture s_menuVisual;
	sf::Sprite s_menuText;


	for (int i = 0; i < NUM_BUTTONS_Save; i++)
	{
		buttonsSave.push_back(s_menuText);
		buttonsTextureSave.push_back(s_menuVisual);


	}

	buttonsTextureSave[0].loadFromFile("res/img/yes_off.png");
	buttonsTextureSave[1].loadFromFile("res/img/no_off.png");


	for (int i = 0; i < NUM_BUTTONS_Save; i++)
	{
		buttonsSave[i].setTexture(buttonsTextureSave[i]);
		sf::FloatRect optionsRect = buttonsSave[i].getLocalBounds();
		buttonsSave[i].setOrigin(optionsRect.left + optionsRect.width / 2.0f,
			optionsRect.top + optionsRect.height / 2.0f);

		buttonsSave[i].setPosition(window.getSize().x / 2.0f, 350.0f + i * 100.0f);
		window.draw(buttonsSave[i]);
	}

	sf::Event event;

	while (window.pollEvent(event))
	{

		if (GameState::isJoysticConnected)
		{
			if (Joystick::isButtonPressed(0, 5)) // Xbox RB
			{
				if (indexSelectionSave < 1)
				{
					indexSelectionSave++;
				}
			}
			else if (Joystick::isButtonPressed(0, 4))
			{
				if (indexSelectionSave > 0)
				{
					indexSelectionSave--;
				}
			}
		}

		switch (event.type)
		{

		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:

			switch (event.key.code)
			{
			case sf::Keyboard::S:
				if (indexSelectionSave < 1)
				{
					indexSelectionSave++;
				}
				break;

			case sf::Keyboard::W:
				if (indexSelectionSave > 0)
				{
					indexSelectionSave--;
				}
				break;
			}
			break;
		}
	}

	switch (indexSelectionSave)
	{
	case 0:
		buttonsTextureSave[indexSelectionSave].loadFromFile("res/img/yes_on.png");
		window.draw(buttonsSave[indexSelectionSave]);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Joystick::isButtonPressed(0, 1) && GameState::isJoysticConnected == true) {

			scoreFile.open("res/scores.txt", std::ios_base::app | std::ios_base::out);
			scoreFile << score << "\n";
			scoreFile.close();
			GameState::currentState = GameState::States::s_exit;

		}

		break;

	case 1:
		buttonsTextureSave[indexSelectionSave].loadFromFile("res/img/no_on.png");
		window.draw(buttonsSave[indexSelectionSave]);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Joystick::isButtonPressed(0, 1) && GameState::isJoysticConnected == true) {
			GameState::currentState = GameState::States::s_exit;
		}
		break;

	default:
		break;
	}
}

