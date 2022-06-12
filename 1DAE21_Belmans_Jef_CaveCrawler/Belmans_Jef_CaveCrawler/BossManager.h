#pragma once
#include "BossEnemy.h" 

enum class GameState;

class BossManager final
{
public:
	BossManager(float left, float bottom, Window window);
	~BossManager() = default;

	void Reset();
	void Update(Avatar& playerAvatar, const Level& level, GameState gameState);
	void Draw() const;
	void DrawHUD() const;
	
private:
	bool m_IsPlayerInBossRoom;
	Rectf m_BossRoom;
	const float m_HealthBarBaseWidth{ 256.0f };
	Rectf m_HealthBarFill;
	Rectf m_HealthBarBorder;
	BossEnemy m_Boss;

	void PlayerOverlapCheck(Avatar& playerAvatar);
	void ProjectileCollisionCheck(Avatar& playerAvatar);
};

