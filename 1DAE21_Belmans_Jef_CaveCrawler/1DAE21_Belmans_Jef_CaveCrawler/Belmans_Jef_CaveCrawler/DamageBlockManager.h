#pragma once
#include <vector>
#include "structs.h"

class Health;
class DamageBlock;
class Camera;
class Avatar;

class DamageBlockManager final
{
public:
	DamageBlockManager() = default;
	~DamageBlockManager();

	DamageBlockManager(const DamageBlockManager& other) = delete;
	DamageBlockManager& operator=(const DamageBlockManager& other) = delete;
	DamageBlockManager(DamageBlockManager&& other) = delete;
	DamageBlockManager& operator=(DamageBlockManager&& other) = delete;

	DamageBlock* AddItem(const Point2f& bottomLeft);
	bool Initialize(const std::string& filePath);

	void Draw() const;
	void Update(Avatar& playerAvatar);

private:
	std::vector<DamageBlock*> m_pItems;

	void PlayerCollisionCheck(Avatar& playerAvatar);
	void DeleteBlock(const DamageBlock* block) const;
};