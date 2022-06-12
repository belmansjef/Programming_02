#pragma once
#include <vector>

class Level;
class string;

class LevelManager
{
public:
	LevelManager();

	void LoadLevelByName(const std::string& levelName);

private:
	std::vector<Level*> m_pLevels;
	Level* m_pCurrentLevel;
};