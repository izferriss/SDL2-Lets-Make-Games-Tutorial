#pragma once

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, int tileSize, int tileScale, std::string id)
	{
		texture = Game::assets->getTexture(id);

		position.x = static_cast<float>(xPos);
		position.y = static_cast<float>(yPos);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = tileSize;
		srcRect.h = tileSize;

		dstRect.x = xPos;
		dstRect.y = yPos;
		dstRect.w = tileSize * tileScale;
		dstRect.h = tileSize * tileScale;
	}

	void update() override
	{
		dstRect.x = static_cast<int>(position.x - Game::camera.x);
		dstRect.y = static_cast<int>(position.y - Game::camera.y);
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
	}
};