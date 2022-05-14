#include "pch.h"
#include "CannonEnemy.h"
#include "utils.h"
#include "Health.h"
#include "SoundManager.h"
#include <algorithm>

CannonEnemy::CannonEnemy(const Point2f& bottomLeft, const CannonOrientation& orientation)
	: m_SpriteBase { SpriteType::cannonEnemyBase }
	, m_SpriteBarrel { SpriteType::cannonEnemyBarrel }
	, m_Health { 3, &m_SpriteBase }
	, m_BaseOrientation { orientation == CannonOrientation::down ? 0.0f : 180.0f }
	, m_BarrelAngle { 0.0f }
	, m_ShotCooldown{ 1.0f }
	, m_LastShotTime{ 0.0f }
	, m_IsPlayerInRange { false }
	, m_Range{ 300.0f }
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
}

void CannonEnemy::TakeDamage(int damage)
{
	m_Health.TakeDamage(damage);
}

void CannonEnemy::Update(const Rectf& actorShape, Health& actorHealth, const std::vector<std::vector<Point2f>>& levelVerts)
{
	const Vector2f freeVec ((actorShape.left + actorShape.width / 2.0f) - m_BaseCenter.x, (actorShape.bottom + actorShape.height / 2.0f) - m_BaseCenter.y);
	m_BarrelAngle = float(int(atan2f(freeVec.y, freeVec.x) * float(180.0f / M_PI) + 360) % 360);

	if (m_BaseOrientation == 0.0f)
	{
		m_BarrelAngle = std::clamp(m_BarrelAngle, 180.0f, 359.0f);
		if (m_BarrelAngle == 180.0f && actorShape.left + actorShape.width / 2.0f > m_BaseCenter.x)
		{
			m_BarrelAngle = 359.0f;
		}
	}
	else
	{
		m_BarrelAngle = std::clamp(m_BarrelAngle, 0.0f, 180.0f);
		if (m_BarrelAngle == 180.0f && actorShape.left + actorShape.width / 2.0f > m_BaseCenter.x)
		{
			m_BarrelAngle = 0.0f;
		}
	}

	const Point2f playerPos{ freeVec.x + m_BaseCenter.x, freeVec.y + m_BaseCenter.y + 16.0f };

	m_IsPlayerInRange = freeVec.Length() <= m_Range;
	utils::HitInfo hitInfo;
	for (std::vector<Point2f> verts : levelVerts)
	{
		if (utils::Raycast(verts, m_BaseCenter, playerPos, hitInfo))
		{
			m_IsPlayerInRange = false;
		}
	}

	if (m_IsPlayerInRange)
	{
		m_SpriteBarrel.SetAnimation("shoot");
	}
	else
	{
		m_SpriteBarrel.SetAnimation("idle");
	}

	if (Time::time > m_LastShotTime + m_ShotCooldown && m_IsPlayerInRange)
	{
		Shoot(freeVec);
	}

	m_ProjectileManager.Update(levelVerts, actorShape);
	m_SpriteBase.Update();
	m_SpriteBarrel.Update();

	if (m_ProjectileManager.HasHitPlayer(actorShape))
	{
		SoundManager::GetInstance()->PlaySound(SoundType::hitHurt);
		actorHealth.TakeDamage(1);
	}
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
		glTranslatef(6.0f, -m_SpriteBarrel.GetFrameHeight() / 2.0f, 0);
		// glRotatef(90.0f, 0, 0, 1);
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

void CannonEnemy::Reset()
{
	m_Health.Heal(3);
}

Rectf CannonEnemy::GetBoxCollider() const
{
	return m_BoxCollider;
}

bool CannonEnemy::IsOverlapping(const Rectf& shape) const
{
	return utils::IsOverlapping(shape, m_BoxCollider);
}

bool CannonEnemy::IsDead() const
{
	return m_Health.GetIsDead();
}

void CannonEnemy::Shoot(const Vector2f& freeVec)
{
	m_ProjectileManager.InstanciateProjectile(freeVec.Normalized() * 100.0f, m_BaseCenter + (freeVec.Normalized() * 12.0f));
	m_LastShotTime = Time::time;
}
