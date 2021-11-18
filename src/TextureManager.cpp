#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* texturePath)
{
	SDL_Surface* tempSurface = IMG_Load(texturePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

SDL_Texture* TextureManager::loadTextureFromText(SDL_Surface* surfaceMessage)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	return texture;

}

void TextureManager::render(SDL_Texture* texture,  SDL_Rect& dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, NULL, &dest, 0, NULL, flip);

}

void TextureManager::render(SDL_Texture* texture, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &src, &dest, 0, NULL, flip);

}

void TextureManager::render(SDL_Texture* texture, SDL_Rect& dest)
{
	SDL_RenderCopy(Game::renderer, texture, NULL, &dest);
}