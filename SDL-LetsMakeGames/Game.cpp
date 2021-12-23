#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

//SDL Event handler
SDL_Event Game::e;

SDL_Rect Game::camera = {0, 0, 800, 160};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());

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

	assets->addTexture("terrain", "assets/map/dungeonTiles.png");
	assets->addTexture("player", "assets/charSheets/player/playerSheet.png");
	assets->addTexture("projectile", "assets/projectiles/test.png");

	map = new Map("terrain", 1, 32);

	//ECS implementation
	map->loadMap("assets/map/dungeon.map", 50, 25);

	player.addComponent<TransformComponent>(1);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	assets->createProjectile(Vector2D(100, 100), Vector2D(1, 0), 1200, 1, "projectile");
	assets->createProjectile(Vector2D(120, 120), Vector2D(2, 1), 1200, 1, "projectile");
	assets->createProjectile(Vector2D(300, 300), Vector2D(-1, 3), 3200, 1, "projectile");
	assets->createProjectile(Vector2D(400, 400), Vector2D(-1, 3), 3200, 1, "projectile");

}//end game::init()

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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
	SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPosition = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect colliderRect = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(colliderRect, playerCollider))
		{
			player.getComponent<TransformComponent>().position = playerPosition;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "projectile hit player" << std::endl;
			p->destroy();
		}
	}

	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

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
	for (auto& c : colliders)
	{
		c->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& p : projectiles)
	{
		p->draw();
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
