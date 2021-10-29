#include "Collision.h"

bool Collision::AABB(const SDL_Rect& objectA, const SDL_Rect& objectB)
{
	if (objectA.x + objectA.w >= objectB.x && objectB.x + objectB.w >= objectA.x && objectA.y + objectA.h >= objectB.y && objectB.y + objectB.h >= objectA.y)
	{
		return true;
	}
}

