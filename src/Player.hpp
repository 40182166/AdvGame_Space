#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
public:
	Player();
	~Player();

	int life;
	void CreateShip(int lifeStart, RenderWindow& window);
	void DrawShip(RenderWindow& window);
	//void shoot();
	void movement(RenderWindow& window);

	Texture texturePlayer;
	Sprite player;
	float thresholdBound = 50.0f;
};

