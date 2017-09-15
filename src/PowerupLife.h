#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;

class PowerupLife : public Object
{
public:
	PowerupLife();
	~PowerupLife();

	int life = 1;
	float movementSpeed = 0.6f;

	bool picked = false;

	void update();

	void movement();

	Texture textureEnemy2;
	Sprite enemy2;
	float thresholdBound = 50.0f;
};