#pragma once
#include <vector>
#include "CrabEnemy.h"

class Camera;
class Projectile;
class Level;
class Avatar;

class CrabEnemyManager final
{
public:
	CrabEnemyManager() = default;
	~CrabEnemyManager();
	CrabEnemyManager(const CrabEnemyManager& other) = delete;
	CrabEnemyManager& operator=(const CrabEnemyManager& other) = delete;
	CrabEnemyManager(CrabEnemyManager&& other) = delete;
	CrabEnemyManager& operator=(CrabEnemyManager&& other) = delete;

	void Initialize(const std::string& filePath);
	CrabEnemy* AddItem(const Point2f& bottomLeft, int movementDirection = 1, int maxHealth = 3);

	void Update(Avatar& playerAvatar, const Level& level, std::vector<Projectile*> pProjectiles);
	void Draw() const;

	void Reset();

private:
	std::vector<CrabEnemy*> m_pItems;

	void PlayerOverlapCheck(Avatar& playerAvatar);
	void ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles);
};