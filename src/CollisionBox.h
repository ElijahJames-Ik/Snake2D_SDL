#pragma once
#include "SDL.h"
// Used for representing map collision locations
class CollisionBox
{
public:
	CollisionBox(SDL_Rect& destRect);
	SDL_Rect& getDestRect();
private:
	SDL_Rect destRect;

};

