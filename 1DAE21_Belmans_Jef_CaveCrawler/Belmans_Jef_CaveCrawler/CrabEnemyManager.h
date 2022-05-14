#pragma once
#include <vector>
#include "CrabEnemy.h"

class Camera;
class Health;
class Projectile;
class Level;
class CrabEnemyManager final
{
public:
	CrabEnemyManager() = default;
	~CrabEnemyManager();
	CrabEnemyManager(const CrabEnemyManager& other) = delete;
	CrabEnemyManager& operator=(const CrabEnemyManager& other) = delete;
	CrabEnemyManager(CrabEnemyManager&& other) = delete;
	CrabEnemyManager& operator=(CrabEnemyManager&& other) = delete;

	CrabEnemy* AddItem(const Point2f& bottomLeft, int movementDirection = 1, int maxHealth = 3);

	void Update(const Rectf& actorShape, const Level& level, std::vector<Projectile*> pProjectiles, Health& actorHealth);
	void Draw() const;

	void Reset();

private:
	std::vector<CrabEnemy*> m_pItems;

	void PlayerOverlapCheck(const Rectf& actorShape, Health& actorHealth);
	void ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles);
};