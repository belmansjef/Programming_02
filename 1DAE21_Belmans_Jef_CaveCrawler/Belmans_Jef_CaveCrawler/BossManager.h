#pragma once
#include "BossEnemy.h" 

enum class GameState;

class BossManager final
{
public:
	BossManager(float left, float bottom);
	~BossManager() = default;

	void Reset();
	void Update(Avatar& playerAvatar, const Level& level, GameState gameState);
	void Draw() const;
	
private:
	BossEnemy m_Boss;

	void PlayerOverlapCheck(Avatar& playerAvatar);
	void ProjectileCollisionCheck(Avatar& playerAvatar);
};

