#pragma once


#include <SDL.h>
#include <iostream>
#include <SDL_image.h>



class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height);
	void handleEvents();
	void update();
	void render();
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isGameRunning;
	static int windowWidth;
	static int windowHeight;

private:
	SDL_Window* gameWindow;
	

	
};