#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

//forward declaration
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int x, int y, int w, int h, bool fullScreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	static void addTile(int srcX, int srcY, int xPos, int yPos);
	static SDL_Renderer* renderer;
	static SDL_Event e;
	static std::vector<ColliderComponent*> colliders;
	static bool isRunning;

	static SDL_Rect camera;

private:
	
	SDL_Window* window;

};

