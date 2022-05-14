#pragma once
#include <vector>
#include "CannonEnemy.h"

class Camera;
class Health;
class Projectile;
class Level;
class CannonEnemyManager final
{
public:
	CannonEnemyManager() = default;
	~CannonEnemyManager();
	CannonEnemyManager(const CannonEnemyManager& other) = delete;
	CannonEnemyManager& operator=(const CannonEnemyManager& other) = delete;
	CannonEnemyManager(CannonEnemyManager&& other) = delete;
	CannonEnemyManager& operator=(CannonEnemyManager&& other) = delete;

	CannonEnemy* AddItem(const Point2f& bottomLeft, const CannonOrientation& orientation);

	void Update(const Rectf& actorShape, Health& actorHealth, const std::vector<std::vector<Point2f>>& levelVerts, std::vector<Projectile*> pProjectiles);
	void Draw() const;

	void Reset();

private:
	std::vector<CannonEnemy*> m_pItems;

	void ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles);
};

