#pragma once
#include <vector>

class Level;

class LevelManager
{
public:
	LevelManager();


private:
	std::vector<Level*> m_pLevels;
};

