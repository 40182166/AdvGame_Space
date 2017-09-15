#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include "Ammo.h"

Ammo::Ammo()
{
	rect.setSize(sf::Vector2f(18, 26));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Green);

	texture.loadFromFile("res/img/ammo.png");
	sprite.setTexture(texture);
	sprite.setScale(Vector2f(0.1f, 0.1f));
}

Ammo::~Ammo()
{
}

void Ammo::shooted()
{
	rect.move(0, -movementSpeed);
	sprite.setPosition(rect.getPosition());
	lasting++;
	if (lasting >= lastingMax)
	{
		collided = true;
	}
}
