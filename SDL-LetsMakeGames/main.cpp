#include "SDL.h"
#include "Game.h"

const int FPS = 60;
const int frameDelay = 1000 / FPS; //maximum amount of work time between frames

Game *game = nullptr;

int main(int argc, char *argv[])
{

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	//Game loop
	while (game->running())
	{
		//Set to how many ms since starting SDL
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		//How long it took before frameStart in ms
		frameTime = SDL_GetTicks() - frameStart;

		//If too quick, go 60FPS
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}