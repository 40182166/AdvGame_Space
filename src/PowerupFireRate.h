#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;

class PowerupFireRate : public Object
{
public:
	PowerupFireRate();
	~PowerupFireRate();

	int life = 1;
	float movementSpeed = 2.0f;

	bool picked = false;

	void update();

	void movement();

	Texture textureEnemy2;
	Sprite enemy2;
	float thresholdBound = 50.0f;
};
