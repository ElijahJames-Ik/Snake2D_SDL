#include "Tile.h"
#include "TextureManager.h"
#include "GlobalData.h"
#include <iostream>

Tile::Tile(const char* textureSheet, int x, int y, int srcX, int srcY) : Actor(textureSheet, x, y, srcX, srcY)
{
	velocity.x = 0;
	velocity.y = 0;
	srcRect.h = GlobalData::tileHeight;
	srcRect.w = GlobalData::tileWidth;
	srcRect.x = srcX;
	srcRect.y = srcY;
	destRect.w = GlobalData::tileWidth;
	destRect.h = GlobalData::tileHeight;
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