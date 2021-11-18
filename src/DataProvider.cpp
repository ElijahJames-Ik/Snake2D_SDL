#include "DataProvider.h"
#include <iostream>



	DataProvider::DataProvider()
	{
		highscoreData = {
			"1st=500",
			"2nd=400",
			"3rd=300",
			"4th=200",
			"5th=100"
		};
		gameData = {
			"Map=0",
			"Difficult=1"
		};
	}

	// check if file exists function
	bool DataProvider::doesFileExist(const std::string& path)
	{
		std::ifstream file(path.c_str());
		return file.good();
	}

	// create a new file
	void DataProvider::createFile(const std::string& path)
	{
		std::ofstream outfile(path);
		outfile.close();
 
	}

	// create game data to file
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

	// get game data from file
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

	// get game highscores from file as vector of strings
	std::vector<std::string> DataProvider::getHighscoresAsListOfStrings(const std::string& path)
	{
		if (!doesFileExist(path))
		{
			createFile(path);
			writeData(path, highscoreData);
			std::cout << "Write data" << std::endl;
		}

		std::vector<std::string> settings;

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
					settings.emplace_back(line);
				}
			};
			mapFile.close();
		}
		return settings;
	}

	// get game data from file
	std::vector<int> DataProvider::getHighscores(const std::string& path)
	{
		if (!doesFileExist(path))
		{
			createFile(path);
			writeData(path, highscoreData);
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

