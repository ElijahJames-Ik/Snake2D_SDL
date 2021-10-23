#include "Actor.h"
#include "TextureManager.h"

Actor::Actor(const char* textureSheet, int x, int y) {
	actorTexture = TextureManager::loadTexture(textureSheet);

	position.x = x;
	position.y = y;
	
}

Actor::~Actor()
{
	SDL_DestroyTexture(actorTexture);
}
