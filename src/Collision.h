#pragma once

#include <SDL.h>

class Collision
{
public:
	// Checks if there is collision between two object
	static bool CheckForCollision(const SDL_Rect& objectA, const SDL_Rect& objectB);

};