#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

//SDL Event handler
SDL_Event Game::e;

SDL_Rect Game::camera = {0, 0, 800, 160};

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());

const char* mapFile = "assets/map/dungeonTiles.png";

//Define groups
enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

//Lists of objects in groups
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

Game::Game()
{}
Game::~Game()
{}

//Initializes SDL subsystems and creates a window and renderer. If successful, private member gameRunning is set to true.
void Game::init(const char* title, int x, int y, int w, int h, bool fullScreen)
{
	//enum handler variable
	int flags = 0;

	//if fullScreen = true
	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//Console output success
		std::cout << "SDL Subsystems successfully initialized!" << std::endl;

		//Create window
		window = SDL_CreateWindow(title, x, y, w, h, flags);

		if (window)
		{
			//Console output success
			std::cout << "Window successfully created!" << std::endl;

			//Create renderer
			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer)
			{
				//Console output success
				std::cout << "Renderer successfully created!" << std::endl;

				//Set render draw color to white
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				//Set game loop flag
				isRunning = true;
			}
			else
			{
				//Set game loop flag
				isRunning = false;
			}
		}
		else
		{
			//Set game loop flag
			isRunning = false;
		}
	}
	else
	{
		//Set game loop flag
		isRunning = false;
	}


	map = new Map();

	//ECS implementation
	Map::loadMap("assets/map/dungeon.map", 50, 25);

	player.addComponent<TransformComponent>(1);
	player.addComponent<SpriteComponent>("assets/charSheets/player/playerSheet.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

}//end game::init()

//Handles SDL-driven events.
void Game::handleEvents()
{
	//Polls for pending events
	SDL_PollEvent(&e);

	//Case-by-case event handler
	switch (e.type)
	{	
	//user requested quit
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}//end game::handleEvents()

//Processes logical functionalities
void Game::update()
{

	manager.refresh();
	manager.update();

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x >= camera.w)
	{
		camera.x = camera.w;
	}
	if (camera.y >= camera.h)
	{
		camera.y = camera.h;
	}

}//end game::update()





//Renders objects to the window.
void Game::render()
{
	//Clear renderer buffer
	SDL_RenderClear(renderer);

	//Textures to be rendered
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}

	//Updates screen
	SDL_RenderPresent(renderer);
}//end game::render()

//Destroys our window, renderer, and exits SDL subsystems.
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}//end game::clean()

void Game::addTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, mapFile);
	tile.addGroup(groupMap);
}
