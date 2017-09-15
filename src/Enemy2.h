#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;

class Enemy2 : public Object
{
public:
	Enemy2();
	~Enemy2();

	int life = 4;
	float movementSpeed = 0.6f;
	int attackDamage = 2;
	bool dead = false;

	void CreateShip(int lifeStart, RenderWindow& window);
	void update();

	void movement();

	Texture textureEnemy2;
	Sprite enemy2;
	float thresholdBound = 50.0f;
};