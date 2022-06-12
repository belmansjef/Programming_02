#include "pch.h"
#include "LevelManager.h"
#include "LevelBase.h"
#include "Level_1.h"
#include "Level_Boss.h"

LevelManager::LevelManager(const Window& window)
	: m_pCurrentLevel { nullptr }
	, m_CurrentLevelIndex { 1 }
{
	m_pLevels.push_back(new Level_1(window));
	m_pLevels.push_back(new Level_Boss(window));

	m_pCurrentLevel = m_pLevels[m_CurrentLevelIndex];
}

LevelManager::~LevelManager()
{
	for (LevelBase* level : m_pLevels)
	{
		delete level;
		level = nullptr;
	}

	m_pCurrentLevel = nullptr;
}


void LevelManager::LoadLevelByName(const std::string& levelName)
{
	for (int i = 0; i < m_pLevels.size(); i++)
	{
		if (m_pLevels[i]->GetLevelName() == levelName)
		{
			m_CurrentLevelIndex = i;
			m_pCurrentLevel = m_pLevels[i];
			return;
		}
	}

	std::cout << "Error loading [" << levelName << "].\r\n";
}

void LevelManager::LoadNextLevel()
{
	
	if (++m_CurrentLevelIndex <= m_pLevels.size() - 1)
	{
		m_pCurrentLevel = m_pLevels[m_CurrentLevelIndex];
	}
	else
	{
		std::cout << "No next level found!\r\n";
	}
}

void LevelManager::Reset()
{
	m_pCurrentLevel->Reset();
}

void LevelManager::Update(MenuManager& menuManager, GameState& currentGameState)
{
	m_pCurrentLevel->Update(currentGameState, menuManager);
}

void LevelManager::Draw(const GameState& currentGameState) const
{
	m_pCurrentLevel->Draw(currentGameState);
}
