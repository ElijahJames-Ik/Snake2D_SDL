#include "Collision.h"

bool Collision::AABB(const SDL_Rect& objectA, const SDL_Rect& objectB)
{
	/*if (objectA.x + objectA.w >= objectB.x && objectB.x + objectB.w >= objectA.x && objectA.y + objectA.h >= objectB.y && objectB.y + objectB.h >= objectA.y)
	{
		return true;
	}*/

	// The sides of the rectangels
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of objectA
	leftA = objectA.x;
	rightA = objectA.x + objectA.w;
	topA = objectA.y;
	bottomA = objectA.y + objectA.h;

	//Calculate the sides of objectB
	leftB = objectB.x;
	rightB = objectB.x + objectB.w;
	topB = objectB.y;
	bottomB = objectB.y + objectB.h;

	if (bottomA <= topB)
	{
		return false;
	}
	if (topA >= bottomB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}

		return true;
}

