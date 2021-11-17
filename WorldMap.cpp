#include "WorldMap.h"
#include "Tile.h"
#include "GlobalData.h"
#include <fstream>
#include <iostream>



WorldMap::WorldMap()
{

}

WorldMap::~WorldMap()
{
	
}


void WorldMap::LoadWorldMap(std::string& path, int tilesX, int tilesY)
{

		
			worldTiles.clear();
			collisionBoxes.clear();
			int srcX;
			std::ifstream mapFile;
			mapFile.open(path);
			std::string line;
			int x = 0;
			int rowCount = 0;
			if (mapFile.is_open() == true)
			{
				for (int y = 0; y < tilesY; y++)
				{
					std::getline(mapFile, line);
					x = 0;
					rowCount = 0;
					for (auto c : line)
					{
						if (c != ',')
						{
							rowCount++;
							srcX = atoi(&c);

							worldTiles.emplace_back(std::make_unique<Tile>(GlobalData::worldMapTexture.c_str(), x * GlobalData::tileWidth, y * GlobalData::tileHeight, srcX * GlobalData::tileWidth, 0));
							x++;
						}
						if (rowCount == tilesX)
						{
							break;
						}
					}
				}


				if (mapFile.peek() != EOF)
				{
					mapFile.ignore();
					// Loaded collision locations on map
					for (int y = 0; y < tilesY; y++)
					{
						std::getline(mapFile, line);
						x = 0;
						for (auto c : line)
						{
							if (c == '2')
							{

								rowCount++;
								srcX = atoi(&c);

								SDL_Rect destRect;
								destRect.x = x * GlobalData::tileWidth;
								destRect.y = y * GlobalData::tileHeight;
								destRect.w = GlobalData::tileWidth;
								destRect.h = GlobalData::tileHeight;

								collisionBoxes.emplace_back(std::make_unique<CollisionBox>(destRect));

							}
							if (c != ',')
							{
								x++;
							}
						}

					}
				}
				mapFile.close();
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