#pragma once
#include <vector>
#include "structs.h"

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

	void Reset();

private:
	std::vector<RisingHand*> m_pItems;

	void PlayerOverlapCheck(const Rectf& actorShape, Health& actorHealth, Camera& cam) const;
	void ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles) const;
};