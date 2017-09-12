#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

using namespace sf;

Player::Player()
{
}


Player::~Player()
{
}

void Player::CreateShip(int lifeStart, RenderWindow& window)
{
	life = lifeStart;
	DrawShip(window);
}

void Player::DrawShip(sf::RenderWindow& window)
{

	texturePlayer.loadFromFile("res/img/player.png");

	Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;

	player.setTexture(texturePlayer);
	player.setScale(Vector2f(0.3f, 0.3f));

	sf::FloatRect spriteBound = player.getLocalBounds();
	player.setOrigin(spriteBound.left + spriteBound.width / 2.0f,
		spriteBound.top + spriteBound.height / 2.0f);
	player.setPosition(sf::Vector2f(width / 2.0f, height - 50));

	movement(window);
	window.draw(player);
}

void Player::movement(sf::RenderWindow& window)
{
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	Vector2f move;
	/*float left = 0.0f + thresholdBound; //useless, but shows the meaning of the threshold
	float right = window.getSize().x - thresholdBound;*/

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		/*if (player.getPosition().x <= left)
		{
			player.setPosition(left, player.getPosition().y);
		}
		else
		{*/
			move.x--;
		//}

		std::cout << player.getPosition().x << "\n";
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		/*if (player.getPosition().x >= right)
		{
			player.setPosition(right, player.getPosition().y);
		}
		else
		{*/
			move.x++;
		//}

		std::cout << player.getPosition().x << "\n";
	}
	player.move(move*300.0f*dt);
}

