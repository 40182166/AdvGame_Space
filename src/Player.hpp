#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;

class Player: public Object
{
public:
	Player();
	~Player();

	int life = 5;
	int score = 0;
	float movementSpeed = 300.0f;
	int attackDamage = 1;
	float fireRate = 0.8f;

	void CreateShip(RenderWindow& window);
	void DrawShip(RenderWindow& window);

	void movement(RenderWindow& window);

	Texture texturePlayer;
	Sprite player;
	float thresholdBound = 50.0f;
};

