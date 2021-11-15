#pragma once
#include<fstream>
#include<string>
#include<vector>
class DataProvider
{
public:

	DataProvider();
	std::vector<int> getGameData(const std::string& path, std::vector<std::string>& data);
	std::vector<std::string> highscoreData;
	std::vector<std::string> gameData;
	void writeData(const std::string& path, std::vector<std::string>& data);
private:
	bool doesFileExist(const std::string& path);
	void createFile(const std::string& path);
	
};