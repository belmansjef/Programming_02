#pragma once
#include <vector>
#include "Vector2f.h"

class Projectile;
class ProjectileManager final
{
public:
	ProjectileManager() = default;
	~ProjectileManager();
	ProjectileManager(const ProjectileManager& other) = delete;
	ProjectileManager& operator=(const ProjectileManager& other) = delete;
	ProjectileManager(ProjectileManager&& other) = delete;
	ProjectileManager& operator=(ProjectileManager&& other) = delete;

	void PoolProjectiles(int nrObjects);
	void InstanciateProjectile(const Vector2f& velocity, const Point2f& bottomLeft);

	void Update(const std::vector<std::vector<Point2f>>& levelVerts);
	void Draw() const;

	void CollisionCheck(const std::vector<std::vector<Point2f>>& levelVerts);

private:
	std::vector<Projectile*> m_Projectiles;
};

