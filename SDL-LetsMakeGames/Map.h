#pragma once
#include <string>

class Map
{
public:
	Map(std::string textureID, int mapScale, int tileSize);
	~Map();
	void loadMap(std::string path, int sizeX, int sizeY);
	void addTile(int srcX, int srcY, int xPos, int yPos);

private:
	std::string textureID;
	int mapScale;
	int tileSize;
	int scaledSize;
};

