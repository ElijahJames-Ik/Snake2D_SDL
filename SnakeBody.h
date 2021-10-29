#pragma once

#include "Actor.h"

class SnakeBody : public Actor
{
public:
	SnakeBody(const char* textureSheet, int x, int y, int width, int height);
	~SnakeBody();

	void update() override;
	void render() override;
	
};