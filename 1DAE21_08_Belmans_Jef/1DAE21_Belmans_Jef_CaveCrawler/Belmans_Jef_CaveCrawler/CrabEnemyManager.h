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

	void Update(const Rectf& actorShape, const Level& level, Health& actorHealth, Camera& cam, std::vector<Projectile*> pProjectiles);
	void Draw() const;

	void Reset();

private:
	std::vector<CrabEnemy*> m_pItems;

	void PlayerOverlapCheck(const Rectf& actorShape, Health& actorHealth, Camera& cam);
	void ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles);
};

