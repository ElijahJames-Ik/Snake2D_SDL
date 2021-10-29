#include "WorldMap.h"
#include "Tile.h"
#include <fstream>
#include <iostream>

const char* defaultMapTexture = "assets/no_barrier_map_texture.png";

WorldMap::WorldMap()
{

}


void WorldMap::LoadWorldMap(std::string path, int tilesX, int tilesY)
{
	int tileY;
	int tileX;
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	if (mapFile.is_open() == true)
	{
		std::cout << "Map file loaded" << std::endl;
		for (int y = 0; y < tilesY; y++)
		{
			for (int x = 0; x < tilesX; x++)
			{
				mapFile.get(c);
				tileX = atoi(&c) * 32;
				mapFile.get(c);
				tileY = atoi(&c) * 32;
				worldTiles.push_back(std::make_unique<Tile>(defaultMapTexture, x * 32, y * 32, tileX, tileY));

			}
		}
	}
	else {
		std::cout << "Couldn't open map File" << std::endl;
	}
}

void WorldMap::render()
{
	for (auto itr = worldTiles.begin(); itr != worldTiles.end(); itr++)
	{
		(*itr)->render();
	}
}