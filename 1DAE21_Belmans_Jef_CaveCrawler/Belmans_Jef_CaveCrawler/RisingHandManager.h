#pragma once
#include <vector>
#include "structs.h"

class Projectile;
class RisingHand;
class Camera;
class Avatar;
class ScoreManager;

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

	void Update(Avatar& playerAvatar, std::vector<Projectile*> pProjectiles, ScoreManager& scoreManager);
	void Draw() const;

	void Reset();

private:
	std::vector<RisingHand*> m_pItems;

	void PlayerOverlapCheck(Avatar& playerAvatar) const;
	void ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles, ScoreManager& scoreManager) const;
};