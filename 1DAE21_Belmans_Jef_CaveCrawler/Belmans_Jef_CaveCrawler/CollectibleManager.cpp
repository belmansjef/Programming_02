#include <iostream>
#include "pch.h"
#include "CollectibleManager.h"
#include "Collectible.h"
#include "Health.h"
#include "SoundManager.h"

CollectibleManager::~CollectibleManager()
{
	for (Collectible* collectible : m_pItems)
	{
		DeleteCollectible(collectible);
	}
}

Collectible* CollectibleManager::AddItem(const Point2f& bottomLeft, Collectible::CollectibleType type)
{
	m_pItems.push_back(new Collectible(bottomLeft, type));
	return m_pItems.back();
}

void CollectibleManager::Update(const Rectf& actorShape, Health& actorHealth)
{
	HitItem(actorShape, actorHealth);
}

void CollectibleManager::Draw() const
{
	for (Collectible* collectible : m_pItems)
	{
		if (collectible->GetIsPickedUp()) continue;
		collectible->Draw();
	}
}

void CollectibleManager::Reset()
{
	for (Collectible* collectible : m_pItems)
	{
		collectible->SetIsPickedUp(false);
	}

	m_NrPointsCollected = 0;
}

bool CollectibleManager::HitItem(const Rectf& rect, Health& actorHealth)
{
	for (Collectible* collectible : m_pItems)
	{
		if (collectible->GetIsPickedUp()) continue;

		if (collectible->IsOverlapping(rect))
		{
			collectible->SetIsPickedUp(true);

			switch (collectible->GetType())
			{
			case Collectible::CollectibleType::points:
				m_NrPointsCollected++;
				SoundManager::GetInstance()->PlaySound(SoundType::coinPickup);
				break;
			case Collectible::CollectibleType::health:
				actorHealth.Heal(1);
				break;
			default:
				break;
			}

			return true;
		}
	}
	
	return false;
}

void CollectibleManager::DeleteCollectible(const Collectible* collectible) const
{
	delete collectible;
	collectible = nullptr;
}
