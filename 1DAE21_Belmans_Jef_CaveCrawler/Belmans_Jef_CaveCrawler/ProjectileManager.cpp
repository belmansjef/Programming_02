#include "ProjectileManager.h"
#include "Projectile.h"
#include "utils.h"

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

void ProjectileManager::Update(const std::vector<std::vector<Point2f>>& levelVerts)
{
	for (Projectile* proj : m_pItems)
	{
		if (proj->IsInstanciated())
		{
			proj->Update();
		}
	}
	
	LevelCollisionCheck(levelVerts);
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
