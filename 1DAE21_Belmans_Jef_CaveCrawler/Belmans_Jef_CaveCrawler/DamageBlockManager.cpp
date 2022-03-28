#include "DamageBlockManager.h"
#include "DamageBlock.h"
#include "Health.h"

DamageBlockManager::DamageBlockManager()
{
}

DamageBlockManager::~DamageBlockManager()
{
	for (DamageBlock* element : m_pItems)
	{
		DeleteBlock(element);
	}
}

DamageBlock* DamageBlockManager::AddItem(const Point2f& bottomLeft)
{
	m_pItems.push_back(new DamageBlock(bottomLeft.x, bottomLeft.y));
	return m_pItems.back();
}

void DamageBlockManager::Draw() const
{
	for (DamageBlock* element : m_pItems)
	{
		element->Draw();
	}
}

void DamageBlockManager::Update(const Rectf& actorShape, Health& actorHealth)
{
	for (DamageBlock* element : m_pItems)
	{
		element->Update();
	}

	CollisionCheck(actorShape, actorHealth);
}

void DamageBlockManager::CollisionCheck(const Rectf& acotrShape, Health& actorHealth)
{
	for (DamageBlock* element : m_pItems)
	{
		if (element->IsOverlapping(acotrShape))
		{
			actorHealth.TakeDamage(1);
		}
	}
}

void DamageBlockManager::DeleteBlock(const DamageBlock* block) const
{
	delete block;
	block = nullptr;
}
