#pragma once


#include "Actor.h"

class SnakeHead : public Actor
{
public:
	SnakeHead(const char* textureSheet, int x, int y, int width, int height);
	~SnakeHead();

	void update() override;
	void render() override;
};