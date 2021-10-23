#pragma once

#include "Game.h"
#include "Vector2D.h"

class Actor {
public: 
	Actor(const char* textureSheet, int x, int y);
	~Actor();

	virtual void update() = 0;
	virtual void render() = 0;

	Vector2D position;
	Vector2D velocity;
	int speed = 2;

	SDL_Texture* actorTexture;
	SDL_Rect srcRect, destRect;
};