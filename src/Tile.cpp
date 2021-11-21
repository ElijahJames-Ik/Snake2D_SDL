#include "Tile.h"
#include "TextureManager.h"
#include "GlobalData.h"
#include <iostream>

Tile::Tile(const char* textureSheet, int x, int y, int srcX, int srcY) : Actor(textureSheet, x, y, srcX, srcY)
{
	setVelocity(Vector2D());
	setSrcRectH(GlobalData::tileHeight);
	setSrcRectW(GlobalData::tileWidth);
	setSrcRectX(srcX);
	setSrcRectY(srcY);
	setDestRectW(GlobalData::tileWidth);
	setDestRectH(GlobalData::tileHeight);
	setDestRectX(x),
	setDestRectY(y);
}
Tile::~Tile()
{

}

void Tile::update()
{

}
void Tile::render()
{
	TextureManager::render(getActorTexture(), getSrcRect(), getDestRect(), getFlipTexture());
}