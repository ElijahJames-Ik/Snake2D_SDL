#include "Tile.h"
#include "TextureManager.h"
#include <iostream>

Tile::Tile(const char* textureSheet, int x, int y, int srcX, int srcY) : Actor(textureSheet, x, y, srcX, srcY)
{
	velocity.x = 0;
	velocity.y = 0;
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = srcX;
	srcRect.y = srcY;
	destRect.w = 32;
	destRect.h = 32;
	destRect.x = x,
	destRect.y = y;
}
Tile::~Tile()
{

}

void Tile::update()
{

}
void Tile::render()
{
	TextureManager::render(actorTexture, srcRect, destRect, flipTexture);
}