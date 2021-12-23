#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int range, int speed, Vector2D velocity)
	{
		this->range = range;
		this->speed = speed;
		this->velocity = velocity;
	}
	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			std::cout << "projectile out of range" << std::endl;
			entity->destroy();
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w || //outside right screen edge
				 transform->position.x < Game::camera.x ||					//outside left screen edge
				 transform->position.y > Game::camera.y + Game::camera.h || //outside bottom screen edge
				 transform->position.y < Game::camera.y)					//outside top screen edge
		{
			std::cout << "projectile out of bounds" << std::endl;
			entity->destroy();
		}
	}


private:
	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;

};