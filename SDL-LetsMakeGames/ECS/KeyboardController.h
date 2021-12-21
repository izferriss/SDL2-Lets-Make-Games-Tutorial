#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::e.type == SDL_KEYDOWN)
		{
			switch (Game::e.key.keysym.sym)
			{
			case SDLK_w: //up
				transform->velocity.y = -1;
				sprite->play("walkUp");
				break;
			case SDLK_a: //left
				transform->velocity.x = -1;
				sprite->play("walkLeft");
				break;
			case SDLK_d: //right
				transform->velocity.x = 1;
				sprite->play("walkRight");
				break;
			case SDLK_s: //down
				transform->velocity.y = 1;
				sprite->play("walkDown");
				break;
			default:
				break;
			}
		}

		if (Game::e.type == SDL_KEYUP)
		{
			switch (Game::e.key.keysym.sym)
			{
			case SDLK_w: //up
				transform->velocity.y = 0;
				sprite->play("idle");
				break;
			case SDLK_a: //left
				transform->velocity.x = 0;
				sprite->play("idle");
				break;
			case SDLK_d: //right
				transform->velocity.x = 0;
				sprite->play("idle");
				break;
			case SDLK_s: //down
				transform->velocity.y = 0;
				sprite->play("idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		}
	}
};
