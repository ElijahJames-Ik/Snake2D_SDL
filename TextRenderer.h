#pragma once
#include <SDL.h>

class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();

private:
	SDL_Surface* surfaceMessage;
	SDL_Texture* message;
};