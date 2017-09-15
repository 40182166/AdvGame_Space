#include "GameState.hpp"
#include "PowerupLife.h"

PowerupLife::PowerupLife()
{
	rect.setSize(sf::Vector2f(90, 82));
	rect.setPosition(400, -10);
	rect.setFillColor(sf::Color::Blue);


	texture.loadFromFile("res/img/powerupLife.png");
	sprite.setTexture(texture);
	sprite.setScale(Vector2f(0.15f, 0.15f));
}

PowerupLife::~PowerupLife()
{
}

void PowerupLife::update()
{
	sprite.setPosition(rect.getPosition());
}

void PowerupLife::movement()
{
	rect.move(0, movementSpeed);
	
}
