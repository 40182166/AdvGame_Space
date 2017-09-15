#include "Enemy1.h"
#include "GameState.hpp"

Enemy1::Enemy1()
{
	rect.setSize(sf::Vector2f(180, 148));
	rect.setPosition(400, -10);
	rect.setFillColor(sf::Color::Blue);

	sf::FloatRect enemy1Rect = sprite.getLocalBounds();
	sprite.setOrigin(enemy1Rect.left + enemy1Rect.width / 2.0f,
		enemy1Rect.top + enemy1Rect.height / 2.0f);
	sprite.setPosition(rect.getPosition().x, rect.getPosition().y - 200);

	texture.loadFromFile("res/img/enemy1ship.png");
	sprite.setTexture(texture);
	sprite.setScale(Vector2f(0.3f, 0.3f));
}

Enemy1::~Enemy1()
{
}

void Enemy1::CreateShip(int lifeStart, RenderWindow & window)
{
}

void Enemy1::DrawShip(RenderWindow & window)
{
}

void Enemy1::movement(RenderWindow & window)
{
	rect.move(0, movementSpeed);
	sprite.setPosition(rect.getPosition());
}
