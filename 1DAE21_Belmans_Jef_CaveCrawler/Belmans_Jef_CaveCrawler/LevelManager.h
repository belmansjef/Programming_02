#pragma once
#include <vector>
#include "Enums.h"

class LevelBase;
class string;
class MenuManager;
class Avatar;

class LevelManager
{
public:
	LevelManager(const Window& window);
	~LevelManager();

	void LoadLevelByName(const std::string& levelName);
	void LoadNextLevel();
	
	void Reset();
	void Update(MenuManager& menuManager, GameState& currentGameState);
	void Draw(const GameState& currentGameState) const;

private:
	std::vector<LevelBase*> m_pLevels;
	int m_CurrentLevelIndex;
	LevelBase* m_pCurrentLevel;
};