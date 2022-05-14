#include "CannonEnemyManager.h"
#include "Level.h"
#include "Projectile.h"

CannonEnemyManager::~CannonEnemyManager()
{
	for (CannonEnemy* element : m_pItems)
	{
		delete element;
		element = nullptr;
	}
}

CannonEnemy* CannonEnemyManager::AddItem(const Point2f& bottomLeft, const CannonOrientation& orientation)
{
	m_pItems.push_back(new CannonEnemy(bottomLeft, orientation));
	return m_pItems.back();
}

void CannonEnemyManager::Update(const Rectf& actorShape, Health& actorHealth, const std::vector<std::vector<Point2f>>& levelVerts, std::vector<Projectile*> pProjectiles)
{
	for (CannonEnemy* element : m_pItems)
	{
		if (!element->IsDead())
		{
			element->Update(actorShape, actorHealth, levelVerts);
		}
	}

	ProjectileCollisionCheck(pProjectiles);
}

void CannonEnemyManager::Draw() const
{
	for (CannonEnemy* element : m_pItems)
	{
		if (!element->IsDead())
		{
			element->Draw();
		}
	}
}

void CannonEnemyManager::Reset()
{
	for (CannonEnemy* element : m_pItems)
	{
		element->Reset();
	}
}

void CannonEnemyManager::ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles)
{
	for (Projectile* projectile : pProjectiles)
	{
		if (!projectile->IsInstanciated()) continue;

		for (CannonEnemy* cannon : m_pItems)
		{
			if (!projectile->IsInstanciated()) break;
			if (cannon->IsDead()) continue;

			if (projectile->HitCheck(cannon->GetBoxCollider())) cannon->TakeDamage(1);
		}
	}
}
