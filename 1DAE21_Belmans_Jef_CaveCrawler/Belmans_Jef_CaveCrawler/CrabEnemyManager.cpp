#include "CrabEnemyManager.h"
#include "Camera.h"
#include "Projectile.h"

CrabEnemyManager::~CrabEnemyManager()
{
	for (CrabEnemy* hand : m_pItems)
	{
		delete hand;
		hand = nullptr;
	}
}

CrabEnemy* CrabEnemyManager::AddItem(const Point2f& bottomLeft, int movementDirection, int maxHealth)
{
	m_pItems.push_back(new CrabEnemy(bottomLeft.x, bottomLeft.y, 24.0f, 11.0f, movementDirection, maxHealth));
	return m_pItems.back();
}

void CrabEnemyManager::Update(const Rectf& actorShape, const Level& level, Health& actorHealth, Camera& cam, std::vector<Projectile*> pProjectiles)
{
	for (CrabEnemy* crab : m_pItems)
	{
		crab->Update(level);
	}

	PlayerOverlapCheck(actorShape, actorHealth, cam);
	ProjectileCollisionCheck(pProjectiles);
}

void CrabEnemyManager::Draw() const
{
	for (CrabEnemy* crab : m_pItems)
	{
		if (!crab->IsDead())
		{
			crab->Draw();
		}
	}
}

void CrabEnemyManager::Reset()
{
	for (CrabEnemy* crab : m_pItems)
	{
		crab->Reset();
	}
}

void CrabEnemyManager::PlayerOverlapCheck(const Rectf& actorShape, Health& actorHealth, Camera& cam)
{
	for (CrabEnemy* crab : m_pItems)
	{
		if (crab->IsOverlapping(actorShape) && actorHealth.ShouldHit() && !crab->IsDead())
		{
			cam.DoScreenShake();
			actorHealth.TakeDamage(1);
		}
	}
}

void CrabEnemyManager::ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles)
{
	for (Projectile* proj : pProjectiles)
	{
		if (proj->IsInstanciated())
		{
			for (CrabEnemy* crab : m_pItems)
			{
				if (proj->HitCheck(crab->GetBoxCollider()))
				{
					crab->TakeDamage(1);
				}
			}
		}
	}
}
