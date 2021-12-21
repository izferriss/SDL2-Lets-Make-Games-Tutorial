#pragma once
#include "Components.h"
#include "../Vector2D.h"
//pos, rot, scale

//Inherits from component class
class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent()
	{
		position.zero();
	}

	TransformComponent(int scale)
	{
		position.x = 400;
		position.y = 320;
		this->scale = scale;
	}

	TransformComponent(float x, float y)
	{
		position.zero();
	}

	TransformComponent(float x, float y, int h, int w, int scale)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		this->scale = scale;
	}

	void init() override
	{
		velocity.zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};