#pragma once

class Menu
{
public:

	virtual void showMenu(sf::RenderWindow& window) = 0;
	virtual void InputHandler(sf::RenderWindow & window) = 0;

};