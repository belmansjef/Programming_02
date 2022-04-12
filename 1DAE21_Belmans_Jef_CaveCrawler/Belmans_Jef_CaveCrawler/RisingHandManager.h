#pragma once
#include <vector>
#include "pch.h"

class Projectile;
class RisingHand;
class Health;
class Camera;
class RisingHandManager final
{
public:
	RisingHandManager() = default;
	~RisingHandManager();
	RisingHandManager(const RisingHandManager& other) = delete;
	RisingHandManager& operator=(const RisingHandManager& other) = delete;
	RisingHandManager(RisingHandManager&& other) = delete;
	RisingHandManager& operator=(RisingHandManager&& other) = delete;

	RisingHand* AddItem(const Point2f& bottomLeft, int maxHealth);

	void Update(const Rectf& actorShape, Health& actorHealth, Camera& cam, std::vector<Projectile*> pProjectiles);
	void Draw() const;

private:
	std::vector<RisingHand*> m_pItems;

	void CollisionCheck(const Rectf& actorShape, Health& actorHealth, Camera& cam);
	void ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles);
};