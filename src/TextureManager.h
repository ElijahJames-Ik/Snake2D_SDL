#pragma once

#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* loadTexture(const char* texture);
	static SDL_Texture* loadTextureFromText(SDL_Surface* surfaceMessage);
	static void render(SDL_Texture* texture, SDL_Rect& dest, SDL_RendererFlip flip);
	static void render(SDL_Texture* texture, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip flip);
	static void render(SDL_Texture* texture, SDL_Rect& dest);
	
};
