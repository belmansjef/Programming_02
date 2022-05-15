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

	void Initialize(const std::string& filePath);
	RisingHand* AddItem(const Point2f& bottomLeft, int maxHealth);

	void Update(const Rectf& actorShape, std::vector<Projectile*> pProjectiles, Health& actorHealth);
	void Draw() const;

	void Reset();

private:
	std::vector<RisingHand*> m_pItems;

	void PlayerOverlapCheck(const Rectf& actorShape, Health& actorHealth) const;
	void ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles) const;
};