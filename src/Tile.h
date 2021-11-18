#pragma once

#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(const char* textureSheet, int x, int y, int srcX, int srcY);
	~Tile();

	void update() override;
	void render() override;

};