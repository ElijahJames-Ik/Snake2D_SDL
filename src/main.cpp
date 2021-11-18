#include "Game.h"



Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int frameRate = 60;
	const int frameDelay = 1000 / frameRate;

	Uint32 frameStart;
	int frameTime;

    game = new Game();
	game->init(GlobalData::windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::windowWidth, Game::windowHeight);

	while (game->isGameRunning)
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	delete game;

	return 0;
}