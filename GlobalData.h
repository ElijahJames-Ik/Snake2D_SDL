#pragma once
#include "SDL.h"
#include<string>


enum class GamePage { HOME, GAME, GAMEOVER, HIGHSCORE, SETTINGS , MAPSETTINGS, DIFFICULT};
enum class MapType {OPEN_FIELD, BOXED_IN};
enum class GameDifficult {EASY, NORMAL, HARD};
class GlobalData
{
public:
	static SDL_Color white;
	static SDL_Color red;
	static SDL_Color green;
	static int currentMenuSelection;
	static int score;
	static bool menuOptionChanged;
	static bool settingsChanged;
	static bool isDataLoadRequired;
	static bool isControllerLocked;
	static bool isInputTextToBeRedrawn;
	static bool isGameOver;
	static bool isFoodManagerResetRequired;
	static bool isHighscoreLoadRequired;
	static bool isReLoadMapRequired;
	static std::string menuItemTextFont;
	static std::string titleTextFont;
	static GamePage currentPage;
	static MapType currentGameMap;
	static GameDifficult gameDifficulty;
	static std::string snakeBodyTexture;
	static std::string highscoreFile;
	static std::string gameSettingsFile;
	static std::string snakeHeadUpTexture;
	static std::string snakeHeadDownTexture;
	static std::string snakeHeadLeftTexture;
	static std::string snakeHeadRightTexture;
	static std::string snakeFoodTexture;
	static std::string snakeBonusFoodTexture;
	static std::string worldMapTexture;
	static std::string tileMapFile;
	static std::string openFieldTexture;
	static std::string openFileMapFile;
	static std::string boxedInFieldTexture;
	static std::string boxedInFileMapFile ;
	static std::string enteredNameTextField;
	static std::string windowTitle;
	

	static int tileWidth;
	static int tileHeight;
	static int snakeSpeed;
	static const int foodWidth = 16;
	static const int foodHeight = 16;
	static const int bonusWidth = 20;
	static const int bonusHeight = 20;
	static const int easySpeed = 1;
	static const int normalSpeed = 2;
	static const int hardSpeed = 3;
	static const int bodyWidth = 8;
	static const int bodyHeight = 8;
	
	
	

	

};