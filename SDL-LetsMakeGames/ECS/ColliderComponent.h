#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;

	TransformComponent* transform;

	ColliderComponent(std::string tag)
	{
		this->tag = tag;
	}

	ColliderComponent(std::string tag, int xPos, int yPos, int size)
	{
		this->tag = tag;
		collider.x = xPos;
		collider.y = yPos;
		collider.h = size;
		collider.w = size;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		texture = TextureManager::loadTexture("assets/map/collisionTile.png");
		srcRect = { 0,0, 32, 32 };
		dstRect = { collider.x, collider.y, collider.w, collider.h };

	}

	void update() override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		dstRect.x = collider.x - Game::camera.x;
		dstRect.y = collider.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
	}
};