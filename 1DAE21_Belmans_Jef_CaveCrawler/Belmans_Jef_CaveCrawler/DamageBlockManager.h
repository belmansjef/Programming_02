#pragma once
#include "pch.h"
#include <vector>

class Health;
class DamageBlock;
class DamageBlockManager final
{
public:
	DamageBlockManager();
	~DamageBlockManager();
	DamageBlockManager(const DamageBlockManager& other) = delete;
	DamageBlockManager& operator=(const DamageBlockManager& other) = delete;
	DamageBlockManager(DamageBlockManager&& other) = delete;
	DamageBlockManager& operator=(DamageBlockManager&& other) = delete;

	DamageBlock* AddItem(const Point2f& center);

	void Draw() const;
	void Update(const Rectf& actorShape, Health& actorHealth);
	void CollisionCheck(const Rectf& acotrShape, Health& actorHealth);

private:
	std::vector<DamageBlock*> m_pItems;

	void DeleteBlock(const DamageBlock* block) const;
};