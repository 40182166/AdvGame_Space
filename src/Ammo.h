#pragma once
#include "Object.h"

using namespace sf;

class Ammo : public Object
{
public:
	Ammo();
	~Ammo();

	float movementSpeed = 2.0f;
	bool collided = false;
	int lastingMax = 1000;
	int lasting = 0;

	void shooted();
};