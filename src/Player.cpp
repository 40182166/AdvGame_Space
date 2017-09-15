#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include "GameState.hpp"

using namespace sf;


Player::Player()
{
}


Player::~Player()
{
}

void Player::CreateShip(RenderWindow& window)
{
	sf::FloatRect playerRect = player.getLocalBounds();
	player.setOrigin(playerRect.left + playerRect.width / 2.0f,
	playerRect.top + playerRect.height / 2.0f);
	player.setPosition(window.getSize().x / 2.0f - thresholdBound, window.getSize().y - thresholdBound * 2);

	rect.setSize(sf::Vector2f(180, 61));
	rect.setPosition(player.getPosition());
	rect.setFillColor(sf::Color::Blue);

}

void Player::DrawShip(sf::RenderWindow& window)
{

	texturePlayer.loadFromFile("res/img/player.png");



	player.setTexture(texturePlayer);
	player.setScale(Vector2f(0.3f, 0.3f));


	movement(window);
	window.draw(player);
}

void Player::movement(sf::RenderWindow& window)
{
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	Vector2f move;
	float left = 0.0f + thresholdBound; //useless, but shows the meaning of the threshold
	float right = window.getSize().x - thresholdBound * 3;

	if (Keyboard::isKeyPressed(Keyboard::A) || Joystick::isButtonPressed(0, 4) && GameState::isJoysticConnected == true) {
		if (player.getPosition().x <= left)
		{
			player.setPosition(left, player.getPosition().y);
		}
		else
		{
			move.x--;
		}

	}
	if (Keyboard::isKeyPressed(Keyboard::D) || Joystick::isButtonPressed(0, 5) && GameState::isJoysticConnected == true) {
		if (player.getPosition().x >= right)
		{
			player.setPosition(right, player.getPosition().y);
		}
		else
		{
			move.x++;
		}

	}
	player.move(move * movementSpeed *dt);
	rect.setPosition(player.getPosition());


}

