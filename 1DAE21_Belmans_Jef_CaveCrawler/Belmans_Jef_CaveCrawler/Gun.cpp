#include "Gun.h"
#include "pch.h"
#include "Projectile.h"

Gun::Gun()
{
	m_ProjectileManager.PoolProjectiles(10);
}

Gun::~Gun()
{
	
}

void Gun::Shoot(const Rectf& actorShape, int horScale)
{
	if (m_LastShotTime + m_FireRate <= Time::time)
	{
		const Vector2f shotVelocity{ horScale > 0 ? m_ShotSpeed : -m_ShotSpeed, 0.0f };
		const Point2f relShootPos{ horScale > 0 ? m_ShootPos.x + actorShape.left : actorShape.left - 4.0f, m_ShootPos.y + actorShape.bottom };
		
		m_ProjectileManager.InstanciateProjectile(shotVelocity, relShootPos);
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
