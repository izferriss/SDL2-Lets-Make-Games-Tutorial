#include "TextureManager.h"

SDL_Texture * TextureManager::loadTexture(const char * fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* returnTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return returnTexture;
}

void TextureManager::draw(SDL_Texture * inTexture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, inTexture, &srcRect, &dstRect, NULL, NULL, flip);
}
