#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"

extern Manager manager;

Map::Map(const char* mapFilePath, int mapScale, int tileSize)
{
	this->mapFilePath = mapFilePath;
	this->mapScale = mapScale;
	this->tileSize = tileSize;
	scaledSize = tileSize * mapScale;
}

Map::~Map()
{

}

void Map::loadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			addTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}

	//Ignore blank line in map file
	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tileCollider(manager.addEntity());
				tileCollider.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tileCollider.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::addTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);
}


