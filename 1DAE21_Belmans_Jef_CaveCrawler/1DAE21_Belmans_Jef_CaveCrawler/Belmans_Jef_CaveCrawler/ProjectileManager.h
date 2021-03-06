#pragma once
#include <vector>

enum class ProjectileType;
class Projectile;
struct Vector2f;

class ProjectileManager final
{
public:
	ProjectileManager() = default;
	~ProjectileManager();

	ProjectileManager(const ProjectileManager& other) = delete;
	ProjectileManager& operator=(const ProjectileManager& other) = delete;
	ProjectileManager(ProjectileManager&& other) = delete;
	ProjectileManager& operator=(ProjectileManager&& other) = delete;

	std::vector<Projectile*> GetProjectiles();
	bool HasHitPlayer(const Rectf& actorShape);

	void PoolProjectiles(int nrObjects, ProjectileType type);
	void InstanciateProjectile(const Vector2f& velocity, const Point2f& bottomLeft);

	void Update(const std::vector<std::vector<Point2f>>& levelVerts, const Rectf& actorShape = {});
	void Draw() const;
	void Reset();

private:
	std::vector<Projectile*> m_pItems;

	void LevelCollisionCheck(const std::vector<std::vector<Point2f>>& levelVerts) const;
};

