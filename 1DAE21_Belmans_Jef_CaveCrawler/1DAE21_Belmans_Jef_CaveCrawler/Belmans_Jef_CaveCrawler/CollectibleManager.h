#pragma once
#include <vector>
#include "structs.h"
#include "Collectible.h"

class Avatar;
class ScoreManager;

class CollectibleManager final
{
public:
	CollectibleManager() = default;
	~CollectibleManager();

	CollectibleManager(const CollectibleManager&) = delete;
	CollectibleManager& operator=(const CollectibleManager&) = delete;
	CollectibleManager(CollectibleManager&&) = delete;
	CollectibleManager& operator=(CollectibleManager&&) = delete;

	void Initliaze(const std::string& filePath);
	Collectible* AddItem(const Point2f& bottomLeft, CollectibleType type);

	void Update(Avatar& playerAvatar, ScoreManager& scoreManager);
	void Draw() const;
	void Reset();

private:
	std::vector<Collectible*> m_pItems;
	int m_NrPointsCollected{ 0 };

	bool HitItem(Avatar& playerAvatar, ScoreManager& scoreManager);
	void DeleteCollectible(const Collectible* collectible) const;
};
