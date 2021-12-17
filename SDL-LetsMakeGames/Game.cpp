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

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());

//Define groups
enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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
	Map::loadMap("assets/map/25x20_world.map", 25, 20);

	player.addComponent<TransformComponent>(2);
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
	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
}//end game::update()


//Lists of objects in groups
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


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

void Game::addTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}
