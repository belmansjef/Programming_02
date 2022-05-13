#include "pch.h"
#include "CannonEnemy.h"
#include "Health.h"

CannonEnemy::CannonEnemy(const Point2f& bottomLeft, float orientation)
	: m_SpriteBase { SpriteType::cannonEnemyBase }
	, m_SpriteBarrel { SpriteType::cannonEnemyBarrel }
	, m_Health { 3, &m_SpriteBase }
	, m_BaseOrientation { orientation }
	, m_BarrelAngle { 0.0f }
	, m_ShotCooldown{ 1.0f }
	, m_LastShotTime{ 0.0f }
{
	m_BoxCollider = Rectf
	(
		bottomLeft.x,
		bottomLeft.y,
		m_SpriteBase.GetFrameWidth(),
		m_SpriteBase.GetFrameHeight()
	);

	m_BaseCenter.x = m_BoxCollider.left + m_BoxCollider.width / 2.0f;
	m_BaseCenter.y = m_BoxCollider.bottom + m_BoxCollider.height / 2.0f;

	m_ProjectileManager.PoolProjectiles(10);
	m_SpriteBarrel.SetAnimation("shoot");
}

void CannonEnemy::Update(const Rectf& actorShape, Health& actorHealth, const std::vector<std::vector<Point2f>>& levelVerts)
{
	const Vector2f freeVec(actorShape.left + actorShape.width / 2.0f - m_BaseCenter.x, actorShape.bottom + actorShape.height / 2.0f - m_BaseCenter.y);
	m_BarrelAngle = atan2f(freeVec.y, freeVec.x) * float(180.0f / M_PI) - 90.0f; // need to offset by -90 degrees because default orientation is up
	
	if (Time::time > m_LastShotTime + m_ShotCooldown)
	{
		Shoot(freeVec);
	}

	m_ProjectileManager.Update(levelVerts, actorHealth, actorShape);
	m_SpriteBarrel.Update();
}

void CannonEnemy::Draw() const
{
	// Draw barrel
	glPushMatrix();
		glTranslatef
		(
			m_BoxCollider.left + m_SpriteBase.GetFrameWidth() / 2.0f
			, m_BoxCollider.bottom + m_SpriteBase.GetFrameHeight() / 2.0f
			, 0
		);
		glRotatef(m_BarrelAngle, 0, 0, 1);
		glTranslatef(- m_SpriteBarrel.GetFrameWidth() / 2.0f, 6.0f, 0);
		m_SpriteBarrel.Draw();
	glPopMatrix();

	// Draw base
	glPushMatrix();
		glTranslatef(m_BoxCollider.left, m_BoxCollider.bottom, 0);
		glRotatef(m_BaseOrientation, 0, 0, 1);
		if (m_BaseOrientation == 180.0f)
		{
			glTranslatef(-m_SpriteBase.GetFrameWidth(), -m_SpriteBase.GetFrameHeight(), 0);
		}
		
		m_SpriteBase.Draw();
	glPopMatrix();

	m_ProjectileManager.Draw();
}

void CannonEnemy::Shoot(const Vector2f& freeVec)
{
	m_ProjectileManager.InstanciateProjectile(freeVec.Normalized() * 100.0f, m_BaseCenter + (freeVec.Normalized() * 12.0f));
	m_LastShotTime = Time::time;
}
