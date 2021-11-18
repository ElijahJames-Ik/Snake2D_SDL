#pragma once

#include "Vector2D.h"
#include "TextureManager.h"


class Actor {
public: 
	Actor(const char* textureSheet, int x, int y, int width, int height);
	Actor(const char* textureSheet, int x, int y, int width, int height, bool animated, int frames, int animationSpeed);
	~Actor();


	virtual void update() = 0;
	virtual void render() = 0;
	void setTexture(const char* filePath);
	void initActor(const char* textureSheet, int x, int y, int width, int height, bool animated,int frames, int animationSpeed);
	Vector2D position;
	Vector2D velocity;
	int speed = 0;
	SDL_RendererFlip flipTexture;
	SDL_Texture* actorTexture;
	SDL_Rect srcRect, destRect;
	int width;
	int height;
	bool isAnimated = false;
	int frames = 0;
	int animationSpeed = 0;
};