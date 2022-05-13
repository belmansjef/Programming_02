#include "ProjectileManager.h"
#include "Projectile.h"
#include "utils.h"
#include "pch.h"
#include "Health.h"

ProjectileManager::~ProjectileManager()
{
	for (Projectile* proj : m_pItems)
	{
		delete proj;
		proj = nullptr;
	}
}

std::vector<Projectile*> ProjectileManager::GetProjectiles()
{
	return m_pItems;
}

void ProjectileManager::PoolProjectiles(int nrObjects)
{
	for (size_t i = 0; i < nrObjects; i++)
	{
		m_pItems.push_back(new Projectile());
	}
}

void ProjectileManager::InstanciateProjectile(const Vector2f& velocity, const Point2f& bottomLeft)
{
	for (Projectile* proj : m_pItems)
	{
		if (!proj->IsInstanciated())
		{
			proj->Instanciate(velocity, bottomLeft);
			return;
		}
	}
}

void ProjectileManager::Update(const std::vector<std::vector<Point2f>>& levelVerts, Health& actorHealth, const Rectf& actorShape)
{
	for (Projectile* proj : m_pItems)
	{
		if (proj->IsInstanciated())
		{
			proj->Update();
		}
	}
	
	LevelCollisionCheck(levelVerts);
	PlayerCollsionCheck(actorShape, actorHealth);
}

void ProjectileManager::Draw() const
{
	for (Projectile* proj : m_pItems)
	{
		if (proj->IsInstanciated())
		{
			proj->Draw();
		}
	}
}

void ProjectileManager::Reset()
{
	for (Projectile* proj : m_pItems)
	{
		proj->Reset();
	}
}

void ProjectileManager::LevelCollisionCheck(const std::vector<std::vector<Point2f>>& levelVerts) const
{
	for (Projectile* proj : m_pItems) 
	{
		if (!proj->IsInstanciated()) continue;

		for (std::vector<Point2f> verts : levelVerts)
		{
			proj->HitCheck(verts);
		}
	}
}

void ProjectileManager::PlayerCollsionCheck(const Rectf& actorShape, Health& actorHealth)
{
	for (Projectile* proj : m_pItems)
	{
		if (proj->IsInstanciated())
		{
			proj->HitCheck(actorShape);
			actorHealth.TakeDamage(1);
		}
	}
}
