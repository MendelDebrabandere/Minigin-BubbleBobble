#pragma once
#include <map>
#include <string>
#include <vector>

//temporarily disable a warning for including rapidjson data
#pragma warning(disable : 4996)
#include <document.h>
#pragma warning(default : 4996)

//==================================
//	This is based on Michiel Dewachtere's HighScoreParser
//	Github: https://github.com/MichielDewachtere/GameEngine/blob/main/BurgerTime/HighScoreParser.h
//==================================

class HighScoreLoader final
{
public:
	static int LoadHighScores(const std::string& fileName);
	static void AddHighScore(const std::string& playerName, int score);
	static std::vector<std::pair<std::string, int>> GetTopFive();

private:
	static void GenerateDefaultJson(const std::string& filename);

	inline static std::map<std::string, int> m_HighScores{};
	inline static rapidjson::Document m_Document{};
	inline static std::string m_FileName{};
};