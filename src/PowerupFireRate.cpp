#include "GameState.hpp"
#include "PowerupFireRate.h"

PowerupFireRate::PowerupFireRate()
{
	rect.setSize(sf::Vector2f(51, 120));
	rect.setPosition(400, -10);
	rect.setFillColor(sf::Color::Blue);


	texture.loadFromFile("res/img/powerupFire.png");
	sprite.setTexture(texture);
	sprite.setScale(Vector2f(0.2f, 0.2f));
}

PowerupFireRate::~PowerupFireRate()
{
}

void PowerupFireRate::update()
{
	sprite.setPosition(rect.getPosition());
}

void PowerupFireRate::movement()
{
	rect.move(0, movementSpeed);
}

