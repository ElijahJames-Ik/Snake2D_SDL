#pragma once
#include<string>
#include<vector>
#include<memory>
#include"Tile.h"

class WorldMap
{
public:
	WorldMap();
	void render();

	void LoadWorldMap(std::string filePath, int tilesX, int tilesY);
private:
	std::vector<std::unique_ptr<Tile>> worldTiles;
};