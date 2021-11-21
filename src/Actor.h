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
	// set actor tecture using texture file
	void setTexture(const char* filePath);
	// initialize actor object
	void initActor(const char* textureSheet, int x, int y, int width, int height, bool animated,int frames, int animationSpeed);
	// get actor position vector
	Vector2D& getPosition();
	// set actor position vector
	void setPosition(Vector2D& newPosition);
	// get actor velocity vector
	Vector2D& getVelocity();
	// set actor velocity vector
	void setVelocity(Vector2D&& newVelocity);
	void setVelocity(Vector2D& newVelocity);
	// get actor movement speed
	int getSpeed();
	// set actor movement speed
	void setSpeed(int speed);
	// get actor render flip object
	SDL_RendererFlip getFlipTexture();
	// set actor render flip object
	void setFlipTexture(SDL_RendererFlip& sdlFlip);
	// get actor texture
	SDL_Texture* getActorTexture();
	// set actor texture using sdl texture object
	void setActorTexture(SDL_Texture* texture);
	// get source rectangle
	SDL_Rect& getSrcRect();
	// set source rectangle
	void setSrcRect(SDL_Rect& rect);
	// get destination rectangle
	SDL_Rect& getDestRect();
	// set destination rectangle
	void setDestRect(SDL_Rect& rect);
	// get actor object width
	int getWidth();
	// set actor object width
	void setWidth(int width);
	// get actor object height
	int getHeight();
	// set actor object height
	void setHeight(int height);
	// get actor object animated state
	bool getAnimationState();
	// set actor object animated state
	void setAnimationState(bool state);
	// get actor object animation frames
	int getAnimationFrames();
	// set actor object animation frames
	void setAnimationsFrames(int frames);
	// get actor object animation speed
	int getAnimationSpeed();
	// set actor object animation speed
	void setAnimationSpeed(int speed);
	// set source rectangle x coordinate value
	void setSrcRectX(int x);
	// set source rectanle  y coordinate value
	void setSrcRectY(int y);
	// set source rectangle width value
	void setSrcRectW(int w);
	// set source rectangle height value
	void setSrcRectH(int h);
	// set destination rectangle x coordinate value
	void setDestRectX(int x);
	// set destination rectangle y coordinate value
	void setDestRectY(int y);
	// set destination rectangle width value
	void setDestRectW(int w);
	// set destination rectangle height value
	void setDestRectH(int h);
	// set position vector x coordinate value
	void setPositionX(int x);
	// set position vector y coordinate value
	void setPositionY(int y);


private:
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