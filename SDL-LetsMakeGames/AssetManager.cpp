#include "AssetManager.h"
#include "ECS/Components.h"
AssetManager::AssetManager(Manager * mgr) : manager(mgr)
{}

AssetManager::~AssetManager()
{}

void AssetManager::createProjectile(Vector2D position, Vector2D velocity, int range, int speed, std::string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(position.x, position.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, velocity);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::addTexture(std::string id, const char * path)
{
	textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture * AssetManager::getTexture(std::string id)
{
	return textures[id];
}
