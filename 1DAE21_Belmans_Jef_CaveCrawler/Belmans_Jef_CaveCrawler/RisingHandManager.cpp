#include "RisingHandManager.h"
#include "RisingHand.h"
#include "Health.h"
#include "Camera.h"
#include "Projectile.h"

RisingHandManager::~RisingHandManager()
{
	for (RisingHand* hand : m_pItems)
	{
		delete hand;
		hand = nullptr;
	}
}

RisingHand* RisingHandManager::AddItem(const Point2f& bottomLeft, int maxHealth)
{
	m_pItems.push_back(new RisingHand(bottomLeft, maxHealth));
	return m_pItems.back();
}

void RisingHandManager::Update(const Rectf& actorShape, Health& actorHealth, Camera& cam, std::vector<Projectile*> pProjectiles)
{
	for (RisingHand* hand : m_pItems)
	{
		if (hand->IsDead()) continue;
		hand->Update(actorShape);
	}

	PlayerOverlapCheck(actorShape, actorHealth, cam);
	ProjectileCollisionCheck(pProjectiles);
}

void RisingHandManager::Draw() const
{
	for (RisingHand* hand : m_pItems)
	{
		if (hand->IsDead()) continue;
		hand->Draw();
	}
}

void RisingHandManager::Reset()
{
	for (RisingHand* hand : m_pItems)
	{
		hand->Reset();
	}
}

void RisingHandManager::PlayerOverlapCheck(const Rectf& actorShape, Health& actorHealth, Camera& cam)
{
	for (RisingHand* hand : m_pItems)
	{
		if (hand->IsOverlapping(actorShape) && actorHealth.ShouldHit() && !hand->IsDead())
		{
			cam.DoScreenShake();
			actorHealth.TakeDamage(1);
		}
	}
}

void RisingHandManager::ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles)
{
	for (Projectile* proj : pProjectiles)
	{
		if (!proj->IsInstanciated()) continue;

		for (RisingHand* hand : m_pItems)
		{
			if (!proj->IsInstanciated()) break;
			if (hand->IsDead()) continue;

			if (proj->HitCheck(hand->GetBoxCollider())) hand->TakeDamage(1);
		}
	}
}
