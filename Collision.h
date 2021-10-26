#pragma once

#include <SDL.h>

class Collision
{
public:
	static bool AABB(const SDL_Rect& objectA, const SDL_Rect& objectB);
	
};