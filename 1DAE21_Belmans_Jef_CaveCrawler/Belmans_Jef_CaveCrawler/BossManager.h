#pragma once
#include "BossEnemy.h" 

enum class GameState;
class ScoreManager;

class BossManager final
{
public:
	BossManager(float left, float bottom, const Window& window);
	~BossManager() = default;

	void Reset();
	void Update(Avatar& playerAvatar, const LevelBase& level, GameState gameState, ScoreManager& scoreManager);
	void Draw() const;
	void DrawHUD() const;
	
private:
	bool m_IsPlayerInBossRoom;
	Rectf m_BossRoom;
	const float m_HealthBarBaseWidth{ 256.0f };
	Rectf m_HealthBarFill;
	Rectf m_HealthBarBorder;
	Rectf m_DoorLeft;
	Rectf m_DoorRight;
	BossEnemy m_Boss;

	void DoorCollisionCheck(Avatar& playerAvatar);
	void PlayerOverlapCheck(Avatar& playerAvatar);
	void ProjectileCollisionCheck(Avatar& playerAvatar, ScoreManager& scoreManager);
};

