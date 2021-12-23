#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"

class AssetManager
{
public:
	AssetManager(Manager* mgr);
	~AssetManager();

	//game objects
	void createProjectile(Vector2D position, Vector2D velocity, int range, int speed, std::string id);


	//texture management
	void addTexture(std::string id, const char* path);
	SDL_Texture* getTexture(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};