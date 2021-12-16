#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent *transform;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		if (Game::e.type == SDL_KEYDOWN)
		{
			switch (Game::e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Game::e.type = SDL_QUIT;
				break;
			case SDLK_w: //up
				transform->velocity.y = -1;
				break;
			case SDLK_a: //left
				transform->velocity.x = -1;
				break;
			case SDLK_d: //right
				transform->velocity.x = 1;
				break;
			case SDLK_s: //down
				transform->velocity.y = 1;
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
				break;
			case SDLK_a: //left
				transform->velocity.x = 0;
				break;
			case SDLK_d: //right
				transform->velocity.x = 0;
				break;
			case SDLK_s: //down
				transform->velocity.y = 0;
				break;
			default:
				break;
			}
		}
	}
};
