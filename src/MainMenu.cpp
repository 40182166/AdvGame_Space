#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "MainMenu.hpp"
#include "GameState.hpp"



void MainMenu::showMenu(sf::RenderWindow &window)
{
	sf::Texture backgroundTexture;
	sf::Sprite background;
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					GameState::changeState(GameState::States::s_play);
				}
				
				break;
			case 1:
				buttonsTexture[indexSelection].loadFromFile("res/img/score_on.png");
				window.draw(buttons[indexSelection]);
				break;
			case 2:
				buttonsTexture[indexSelection].loadFromFile("res/img/exit_on.png");
				window.draw(buttons[indexSelection]);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					window.close();
				}
				break;

			default:
				break;
			}
}

