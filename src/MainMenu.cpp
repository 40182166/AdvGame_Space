#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "MainMenu.hpp"
#include "GameState.hpp"

bool MainMenu::isPlaying = false;
sf::Texture backgroundTexture;
sf::Sprite background;

sf::Texture backgroundScoreTexture;
sf::Sprite backgroundScore;

void MainMenu::showMenu(sf::RenderWindow &window)
{

	backgroundTexture.loadFromFile("res/img/backgroundMenu.jpg");
	sf::Vector2f targetSize(window.getSize().x, window.getSize().y);
	background.setTexture(backgroundTexture);
	background.setScale(
		targetSize.x / background.getLocalBounds().width,
		targetSize.y / background.getLocalBounds().height);
	
	window.draw(background);

	sf::Text title;
	sf::Font fontTitle;
	fontTitle.loadFromFile("res/img/agencyb.ttf");
	title.setFont(fontTitle);
	title.setCharacterSize(150);                       
	title.setColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	title.setString("CAT INVADERS");

	sf::FloatRect textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 100.0f));

	window.draw(title);

	sf::Texture menuVisual;
	sf::Sprite menuText;


	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		buttons.push_back(menuText);
		buttonsTexture.push_back(menuVisual);
		buttons[i].setPosition(100.0f, 350.0f + i * 100.0f);
	}

	buttonsTexture[0].loadFromFile("res/img/play_off.png");
	buttonsTexture[1].loadFromFile("res/img/score_off.png");
	buttonsTexture[2].loadFromFile("res/img/exit_off.png");

	
	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		buttons[i].setTexture(buttonsTexture[i]);
		window.draw(buttons[i]);
	}

	InputHandler(window);

}

void MainMenu::InputHandler(sf::RenderWindow & window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{

		if (GameState::isJoysticConnected)
		{
			if (Joystick::isButtonPressed(0, 5)) // Xbox RB
			{
				if (indexSelection < 2)
				{
					indexSelection++;
				}
			}
			else if (Joystick::isButtonPressed(0, 4))
			{
				if (indexSelection > 0)
				{
					indexSelection--;
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
							if (indexSelection < 2)
							{ 
								indexSelection++;
							}
							break;

						case sf::Keyboard::W:
							if (indexSelection > 0)
							{
								indexSelection--;
							}
							break;
				}
			break;
		}
	}

			switch (indexSelection)
			{
			case 0:
				buttonsTexture[indexSelection].loadFromFile("res/img/play_on.png");
				window.draw(buttons[indexSelection]);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Joystick::isButtonPressed(0, 1) && GameState::isJoysticConnected == true) {
					GameState::currentState = GameState::States::s_play;
				}
				
				break;
			case 1:
				buttonsTexture[indexSelection].loadFromFile("res/img/score_on.png");
				window.draw(buttons[indexSelection]);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Joystick::isButtonPressed(0, 1) && GameState::isJoysticConnected == true) {
					GameState::currentState = GameState::States::s_score;
				}
				break;
			case 2:
				buttonsTexture[indexSelection].loadFromFile("res/img/exit_on.png");
				window.draw(buttons[indexSelection]);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Joystick::isButtonPressed(0, 1) && GameState::isJoysticConnected == true) {
					GameState::currentState = GameState::States::s_exit;
				}
				break;

			default:
				break;
			}
}

void MainMenu::showHighScore(sf::RenderWindow & window)
{

	backgroundScoreTexture.loadFromFile("res/img/backgroundMenu.jpg");
	sf::Vector2f targetSize(window.getSize().x, window.getSize().y);
	backgroundScore.setTexture(backgroundScoreTexture);
	backgroundScore.setScale(
		targetSize.x / backgroundScore.getLocalBounds().width,
		targetSize.y / backgroundScore.getLocalBounds().height);

	window.draw(backgroundScore);

	sf::Text title;
	sf::Font fontTitle;
	fontTitle.loadFromFile("res/img/agencyb.ttf");
	title.setFont(fontTitle);
	title.setCharacterSize(100);
	title.setColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	title.setString("Top High Scores");

	sf::FloatRect textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 100.0f));

	window.draw(title);

	sf::Texture backTexture;
	sf::Sprite back;

	backTexture.loadFromFile("res/img/back.png");
	back.setTexture(backTexture);
	

	sf::FloatRect backRect = back.getLocalBounds();
	back.setOrigin(backRect.left + backRect.width / 2.0f,
		backRect.top + backRect.height / 2.0f);
	back.setPosition(sf::Vector2f(100.0f, window.getSize().y - 100.0f));

	window.draw(back);


	std::ifstream myScores("res/scores.txt");

	std::vector<int> numbers;
	std::vector<int> temp_score;

	int this_score;

	while (myScores >> this_score)
		numbers.push_back(this_score);

	std::sort(numbers.rbegin(), numbers.rend());

	if (numbers.size() > 5)
	{
		for (int i = 0; i < 5; i++)
		{
			temp_score.push_back(numbers[i]);
		}
		std::sort(temp_score.rbegin(), temp_score.rend());
	}
	else
	{
		for (int i = 0; i < numbers.size(); i++)
		{
			temp_score.push_back(numbers[i]);
		}
		std::sort(temp_score.rbegin(), temp_score.rend());
	}

	for (int i = 0; i < temp_score.size(); i++)
	{
		std::ostringstream topScore;
		topScore << temp_score[i];

		sf::Text topScoreText;

		topScoreText.setFont(fontTitle);
		topScoreText.setCharacterSize(40);
		topScoreText.setColor(sf::Color::White);
		topScoreText.setStyle(sf::Text::Bold);
		topScoreText.setString(topScore.str());
		topScoreText.setPosition(100.0f, 200.0f + i * 60.0f);

		window.draw(topScoreText);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || Joystick::isButtonPressed(0, 1) && GameState::isJoysticConnected == true) {
		GameState::currentState = GameState::States::s_menu;
	}


}

