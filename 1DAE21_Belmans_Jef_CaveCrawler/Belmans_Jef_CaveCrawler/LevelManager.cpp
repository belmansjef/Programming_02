#include "pch.h"
#include "LevelManager.h"
#include "Level.h"
#include "Level_1.h"

LevelManager::LevelManager()
{
}

void LevelManager::LoadLevelByName(const std::string& levelName)
{
	for (Level* level : m_pLevels)
	{
		if (level->GetLevelName() == levelName)
		{
			m_pCurrentLevel = level;
			return;
		}
	}

	std::cout << "Error loading [" << levelName << "].\r\n";
}
