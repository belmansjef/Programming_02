#pragma once
#include "LevelBase.h"
#include "CollectibleManager.h"
#include "DamageBlockManager.h"
#include "RisingHandManager.h"
#include "CrabEnemyManager.h"
#include "CannonEnemyManager.h"
#include "FallingSpikeManager.h"
#include "Lava.h"

class Level_1 final : public LevelBase
{
public:
	Level_1(const Window& window);

	Level_1(const Level_1& other) = delete;
	Level_1& operator=(const Level_1& other) = delete;
	Level_1(Level_1&& other) = delete;
	Level_1& operator=(Level_1&& other) = delete;
	
	virtual void Reset() override;
	virtual void Draw(const GameState& currentGameState) const override;
	virtual void Update(GameState& currentGameState, MenuManager& menuManager, ScoreManager& scoreManager) override;

private:
	CollectibleManager m_CollectibleManager;
	DamageBlockManager m_DamageBlockManager;
	RisingHandManager m_RisingHandManager;
	CrabEnemyManager m_CrabEnemyManager;
	CannonEnemyManager m_CannonEnemyManager;
	FallingSpikeManager m_FallingSpikeManager;
	Lava m_Lava{ Point2f(448.0f, 8.0f), 32.0f, 24.0f };

	virtual void PlayerFinished(GameState& currentGameState, MenuManager& menuManager, ScoreManager& scoreManager) override;
};

