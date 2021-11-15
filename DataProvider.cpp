#pragma once
#include "DataProvider.h"
#include <iostream>



	DataProvider::DataProvider()
	{
		highscoreData = {
			"1st=5000",
			"2nd=4000",
			"3rd=3000",
			"4th=2000",
			"5th=1000"
		};
		gameData = {
			"Map=0",
			"Difficult=1"
		};
	}

	bool DataProvider::doesFileExist(const std::string& path)
	{
		std::ifstream file(path.c_str());
		return file.good();
	}

	void DataProvider::createFile(const std::string& path)
	{
		std::ofstream outfile(path);
		outfile.close();
 
	}

	void DataProvider::writeData(const std::string& path, std::vector<std::string>& data)
	{
		std::ofstream file;
		file.open(path);
		std::string line;
		if (file.is_open() == true)
		{
			for (int i = 0; i < data.size(); i++)
			{
				file << data[i] + "\n";
			}
			file.close();
		}
	}

	std::vector<int> DataProvider::getGameData(const std::string& path, std::vector<std::string>& data)
	{
		if (!doesFileExist(path))
		{
			createFile(path);
			writeData(path, data);
			std::cout << "Write data" << std::endl;
		}

		std::vector<int> settings;

		std::ifstream mapFile;
		mapFile.open(path);
		std::string line;
		if (mapFile.is_open() == true)
		{
			while (mapFile.eof() == false)
			{
				std::getline(mapFile, line);
				if (line.empty() != true)
				{
					size_t pos = line.find('=');
					if (pos >= 0)
					{
						pos++;
						std::string str = line.substr(pos);
						int value = stoi(str);
						settings.push_back(value);
					}
				}
				

			};
			mapFile.close();
		}

		return settings;
	}
