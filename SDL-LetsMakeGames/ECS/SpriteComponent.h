#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

//Inherits from Component class
class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, dstRect;

	bool animated = false;
	int frames = 0;
	//delay between frames in ms
	int speed = 100;

public:
	int animationIndex = 0;

	std::map<const char*, Animation> animations;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;
		Animation idle = Animation(0, 8, 100);
		Animation walkLeft = Animation(1, 8, 100);
		Animation walkRight = Animation(2, 8, 100);
		Animation walkUp = Animation(3, 8, 100);
		Animation walkDown = Animation(4, 8, 100);

		animations.emplace("idle", idle);
		animations.emplace("walkLeft", walkLeft);
		animations.emplace("walkRight", walkRight);
		animations.emplace("walkUp", walkUp);
		animations.emplace("walkDown", walkDown);


		play("idle");
		setTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::loadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animationIndex * transform->height;

		dstRect.x = static_cast<int>(transform->position.x);
		dstRect.y = static_cast<int>(transform->position.y);
		dstRect.w = transform->width * transform->scale;
		dstRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, dstRect);
	}

	void play(const char* animationName)
	{
		frames = animations[animationName].frames;
		animationIndex = animations[animationName].index;
		speed = animations[animationName].speed;
	}
};
