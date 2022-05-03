#include "Gun.h"
#include "pch.h"
#include "Projectile.h"
#include "ProjectileManager.h"

Gun::Gun()
{
	m_ProjectileManager.PoolProjectiles(10);
}

Gun::~Gun()
{
	m_ProjectileManager.~ProjectileManager();
}

ProjectileManager& Gun::GetProjectileManager()
{
	return m_ProjectileManager;
}

void Gun::Shoot(const Point2f& actorPos, int horScale)
{
	if (m_LastShotTime + m_FireRate <= Time::time)
	{
		const Vector2f projectileVelocity{ horScale > 0 ? m_ShotSpeed : -m_ShotSpeed, 0.0f };
		const Point2f relShootPos{ horScale > 0 ? m_ShootPos.x + actorPos.x : actorPos.x - 6.0f, m_ShootPos.y + actorPos.y };
		
		m_ProjectileManager.InstanciateProjectile(projectileVelocity, relShootPos);
		m_LastShotTime = Time::time;
	}
}

void Gun::Update(const std::vector<std::vector<Point2f>>& levelVerts)
{
	m_ProjectileManager.Update(levelVerts);
}

void Gun::Draw() const
{
	m_ProjectileManager.Draw();
}
