#include <algorithm>
#include "pch.h"
#include "CannonEnemy.h"
#include "utils.h"
#include "Health.h"
#include "Avatar.h"
#include "SoundManager.h"
#include "ParticleSystem.h"
#include "Enums.h"

CannonEnemy::CannonEnemy(const Point2f& bottomLeft, const CannonOrientation& orientation)
	: m_SpriteBase { SpriteType::cannonEnemyBase }
	, m_SpriteBarrel { SpriteType::cannonEnemyBarrel }
	, m_Health { 3, &m_SpriteBase, 0.1f }
	, m_BaseOrientation { orientation == CannonOrientation::down ? 0.0f : 180.0f }
	, m_BarrelAngle { 0.0f }
	, m_ShotCooldown{ 1.0f }
	, m_LastShotTime{ 0.0f }
	, m_IsPlayerInRange { false }
	, m_Range{ 300.0f }
	, m_pDeathPS { new ParticleSystem(15) }
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

	m_ProjectileManager.PoolProjectiles(10, ProjectileType::big);
	m_pDeathPS->Initialize(Point2f(-20.0f, -20.0f), Point2f{ 20.0f, 20.0f }, Point2f(2.0f, 3.0f), Point2f(0.1f, 0.1f), Point2f(1.5f, 2.5f));
}

CannonEnemy::~CannonEnemy()
{
	delete m_pDeathPS;
	m_pDeathPS = nullptr;
}

void CannonEnemy::Update(Avatar& playerAvatar, const std::vector<std::vector<Point2f>>& levelVerts)
{
	if (!m_Health.GetIsDead())
	{
		const Rectf actorShape = playerAvatar.GetShape();
		const Vector2f freeVec((actorShape.left + actorShape.width / 2.0f) - m_BaseCenter.x, (actorShape.bottom + actorShape.height / 2.0f) - m_BaseCenter.y);
		m_BarrelAngle = float(int(atan2f(freeVec.y, freeVec.x) * float(180.0f / M_PI) + 360) % 360);

		m_IsPlayerInRange = freeVec.Length() <= m_Range;

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

		SetAnimation();

		const Point2f playerPos{ actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.height / 2.0f };
		utils::HitInfo hitInfo;
		for (std::vector<Point2f> verts : levelVerts)
		{
			if (utils::Raycast(verts, m_BaseCenter, playerPos, hitInfo))
			{
				m_IsPlayerInRange = false;
			}
		}

		if (Time::GetInstance()->m_Time > m_LastShotTime + m_ShotCooldown && m_IsPlayerInRange)
		{
			Shoot(freeVec);
		}
		

		m_SpriteBase.Update();
		m_SpriteBarrel.Update();
	}

	UpdateProjectiles(playerAvatar, levelVerts);
	m_pDeathPS->Update();
}

void CannonEnemy::Draw() const
{
	if (!m_Health.GetIsDead())
	{
		DrawBarrel();
		DrawBase();
	}
	m_ProjectileManager.Draw();
	m_pDeathPS->Draw();
}

void CannonEnemy::Reset()
{
	m_Health.Heal(3);
	m_ProjectileManager.Reset();
}

void CannonEnemy::TakeDamage(int damage)
{
	m_Health.TakeDamage(damage);
	if (m_Health.GetIsDead() && !m_pDeathPS->IsPlaying())
	{
		m_pDeathPS->PlayAtPos(Point2f(m_BoxCollider.left + m_BoxCollider.width / 2.0f, m_BoxCollider.bottom + m_BoxCollider.height / 2.0f));
	}
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
	m_LastShotTime = Time::GetInstance()->m_Time;
	SoundManager::GetInstance()->PlaySound(SoundType::cannonShoot);
}

void CannonEnemy::DrawBarrel() const
{
	glPushMatrix();
		glTranslatef
		(
			m_BoxCollider.left + m_SpriteBase.GetFrameWidth() / 2.0f
			, m_BoxCollider.bottom + m_SpriteBase.GetFrameHeight() / 2.0f
			, 0
		);
		glRotatef(m_BarrelAngle, 0, 0, 1);
		glTranslatef(6.0f, -m_SpriteBarrel.GetFrameHeight() / 2.0f, 0);
		m_SpriteBarrel.Draw();
	glPopMatrix();
}

void CannonEnemy::DrawBase() const
{
	glPushMatrix();
		glTranslatef(m_BoxCollider.left, m_BoxCollider.bottom, 0);
		glRotatef(m_BaseOrientation, 0, 0, 1);
		if (m_BaseOrientation == 180.0f)
		{
			glTranslatef(-m_SpriteBase.GetFrameWidth(), -m_SpriteBase.GetFrameHeight(), 0);
		}

		m_SpriteBase.Draw();
	glPopMatrix();
}

void CannonEnemy::SetAnimation()
{
	if ((Time::GetInstance()->m_Time < m_LastShotTime + m_ShotCooldown / 3.0f) && m_IsPlayerInRange)
	{
		m_SpriteBarrel.SetAnimation("shot");
	}
	else
	{
		m_SpriteBarrel.SetAnimation("idle");
	}
}

void CannonEnemy::UpdateProjectiles(Avatar& playerAvatar, const std::vector<std::vector<Point2f>>& levelVerts)
{
	const Rectf actorShape{ playerAvatar.GetShape() };
	m_ProjectileManager.Update(levelVerts, actorShape);
	if (m_ProjectileManager.HasHitPlayer(actorShape))
	{
		SoundManager::GetInstance()->PlaySound(SoundType::hitHurt);
		playerAvatar.TakeDamage(1);
	}
}
