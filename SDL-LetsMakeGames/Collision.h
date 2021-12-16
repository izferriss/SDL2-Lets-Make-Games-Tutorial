#pragma once
#include "SDL.h"
#include "ECS\ColliderComponent.h"

//forward declaration
class ColliderComponent;

class Collision
{
public:
	//Axis-Aligned Bounding Box
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB);

};