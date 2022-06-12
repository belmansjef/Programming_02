#pragma once
#include "LevelBase.h"
#include "BossManager.h"

class Level_Boss final : public LevelBase
{
public:
	Level_Boss(const Window& window);
	~Level_Boss() = default;

	virtual void Reset() override;
	virtual void Draw(const GameState& currentGameState) const override;
	virtual void Update(GameState& currentGameState, MenuManager& menuManager) override;

private:
	BossManager m_BossManager;
};