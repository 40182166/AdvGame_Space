#include "GameState.hpp"
#include "Enemy2.h"

Enemy2::Enemy2()
{
	rect.setSize(sf::Vector2f(150, 85));
	rect.setPosition(400, -10);
	rect.setFillColor(sf::Color::Blue);

	texture.loadFromFile("res/img/enemy2ship.png");
	sprite.setTexture(texture);
}

Enemy2::~Enemy2()
{
}

void Enemy2::CreateShip(int lifeStart, RenderWindow & window)
{
}

void Enemy2::update()
{
	sprite.setPosition(rect.getPosition().x, rect.getPosition().y);
}


void Enemy2::movement()
{
	rect.move(0, movementSpeed);
}
