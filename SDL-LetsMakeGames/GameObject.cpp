#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objectTexture = TextureManager::loadTexture(textureSheet);

	xPos = x;
	yPos = y;
}

void GameObject::update()
{
	srcRect.w = 32;
	srcRect.h = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.w = srcRect.w;
	dstRect.h = srcRect.h;
	dstRect.x = xPos;
	dstRect.y = yPos;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &dstRect);
}