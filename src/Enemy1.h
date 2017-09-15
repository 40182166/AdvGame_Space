#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;

class Enemy1 : public Object
{
public:
	Enemy1();
	~Enemy1();

	int life = 2;
	float movementSpeed = 0.5f;
	int attackDamage = 1;
	bool dead = false;

	void CreateShip(int lifeStart, RenderWindow& window);
	void DrawShip(RenderWindow& window);

	void movement(RenderWindow& window);

	Texture textureEnemy1;
	Sprite enemy1;
	float thresholdBound = 50.0f;
};