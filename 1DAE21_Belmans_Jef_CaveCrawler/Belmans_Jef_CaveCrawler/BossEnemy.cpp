#include "BossEnemy.h"
#include "pch.h"
#include "Time.h"
#include "Enums.h"
#include "Avatar.h"
#include "LevelBase.h"
#include "ParticleSystem.h"
#include "SoundManager.h"
#include "Camera.h"

BossEnemy::BossEnemy(float left, float bottom)
	: m_StartPos{ left, bottom }
	, m_SpriteBody { SpriteType::boss }
	, m_SpriteBarrel { SpriteType::cannonEnemyBarrel }
	, m_PhysicsBody{ left, bottom, m_SpriteBody.GetFrameWidth(), m_SpriteBody.GetFrameHeight(), 175.0f}
	, m_Health { m_MaxHealth, &m_SpriteBody, 0.0f }
	, m_MovementDirection { 1 }
	, m_LastGroundedTime{ 0.0f }
	, m_CurrentState { BossState::landed }
	, m_pDeathPS{ new ParticleSystem(15) }
	, m_pLandPS { new ParticleSystem(15) }
	, m_ShotCooldown{ 1.5f }
	, m_LastShotTime { 0.0f }
	, m_BarrelAngle { 0.0f }
{
	m_ProjectileManager.PoolProjectiles(10, ProjectileType::big);
	m_pDeathPS->Initialize(Point2f(-20.0f, -20.0f), Point2f{ 20.0f, 20.0f }, Point2f(2.0f, 3.0f), Point2f(0.1f, 0.1f), Point2f(1.5f, 2.5f));
	m_pLandPS->Initialize(Point2f(-40.0f, -2.0f), Point2f{ 40.0f, 10.0f }, Point2f(1.5f, 2.0f), Point2f(0.1f, 0.1f), Point2f(2.5f, 3.5f));

}

BossEnemy::~BossEnemy()
{
	delete m_pDeathPS;
	delete m_pLandPS;

	m_pDeathPS = nullptr;
	m_pLandPS = nullptr;
}

bool BossEnemy::IsOverlapping(const Rectf& otherShape) const
{
	return utils::IsOverlapping(otherShape, m_PhysicsBody.GetShape());
}

bool BossEnemy::IsDead() const
{
	return m_Health.GetIsDead();
}

int BossEnemy::GetHealth() const
{
	return m_Health.GetCurrentHealth();
}

int BossEnemy::GetMaxHealth() const
{
	return m_MaxHealth;
}

Rectf BossEnemy::GetBoxCollider() const
{
	return m_PhysicsBody.GetShape();
}

void BossEnemy::PlayerEnteredRoom()
{
	m_LastGroundedTime = Time::GetInstance()->m_Time;
	m_LastShotTime = Time::GetInstance()->m_Time;
}

void BossEnemy::TakeDamage(int damage)
{
	m_Health.TakeDamage(damage);
	if (m_Health.GetIsDead() && !m_pDeathPS->IsPlaying())
	{
		m_pDeathPS->PlayAtPos(m_PhysicsBody.GetCenter());
	}
}

void BossEnemy::Reset()
{
	m_Health.Heal(m_MaxHealth);
	m_PhysicsBody.Shape().left = m_StartPos.x;
	m_PhysicsBody.Shape().bottom = m_StartPos.y;
	m_PhysicsBody.Velocity() = Vector2f();
	m_PhysicsBody.SetHasJumped(false);

	m_SpriteBody.SetAnimation("landed");
	m_CurrentState = BossState::landed;
	m_MovementDirection = 1;
	m_LastGroundedTime = Time::GetInstance()->m_Time;

	m_ProjectileManager.Reset();
}

void BossEnemy::Update(Avatar& playerAvatar, const LevelBase& level)
{
	if (!IsDead())
	{
		const Rectf actorShape = playerAvatar.GetShape();
		const Vector2f freeVec((actorShape.left + actorShape.width / 2.0f) - m_PhysicsBody.GetCenter().x, (actorShape.bottom + actorShape.height / 2.0f) - m_PhysicsBody.GetCenter().y);
		m_BarrelAngle = float(int(atan2f(freeVec.y, freeVec.x) * float(180.0f / M_PI) + 360) % 360);

		if (Time::GetInstance()->m_Time > m_LastShotTime + m_ShotCooldown)
		{
			Shoot(freeVec);
		}

		if (playerAvatar.GetShape().left < m_PhysicsBody.GetPosition().x)
		{
			m_MovementDirection = -1;
		}
		else
		{
			m_MovementDirection = 1;
		}

		SetState();
		m_PhysicsBody.Update(level);
		m_SpriteBody.Update();
		m_SpriteBarrel.Update();
	}
	
	UpdateProjectiles(playerAvatar, level.GetLevelVerts());
	m_pDeathPS->Update();
	m_pLandPS->Update();
}

void BossEnemy::Draw() const
{
	if (!IsDead())
	{
		glPushMatrix();
			glTranslatef(m_PhysicsBody.GetPosition().x, m_PhysicsBody.GetPosition().y, 0);
			m_SpriteBody.Draw();
		glPopMatrix();
		DrawBarrel();
	}
	
	m_ProjectileManager.Draw();
	m_pDeathPS->Draw();
	m_pLandPS->Draw();
}

void BossEnemy::SetState()
{
	if (Time::GetInstance()->m_Time >= m_LastGroundedTime + m_StandTime && m_CurrentState == BossState::landed)
	{
		m_CurrentState = BossState::pre_charge;
		m_SpriteBody.SetAnimation("pre_charge");
	}
	else if (Time::GetInstance()->m_Time >= m_LastGroundedTime + m_StandTime + m_PreChargeTime && m_CurrentState == BossState::pre_charge)
	{
		m_CurrentState = BossState::charge;
		m_SpriteBody.SetAnimation("charge");
	}
	else if (Time::GetInstance()->m_Time >= m_LastGroundedTime + m_StandTime + m_PreChargeTime + m_ChargeTime && m_CurrentState == BossState::charge)
	{
		m_PhysicsBody.Jump();
		m_CurrentState = BossState::in_air;
		m_SpriteBody.SetAnimation("in_air");
		m_PhysicsBody.Velocity().x = m_HorizontalMovementSpeed * m_MovementDirection;
	}

	if (m_PhysicsBody.GetIsGrounded() && m_CurrentState == BossState::in_air && Time::GetInstance()->m_Time >= m_LastGroundedTime + m_StandTime + m_PreChargeTime + m_ChargeTime + 1.0f)
	{
		m_LastGroundedTime = Time::GetInstance()->m_Time;
		m_CurrentState = BossState::landed;
		m_SpriteBody.SetAnimation("landed");
		m_PhysicsBody.SetHasJumped(false);
		m_PhysicsBody.Velocity().x = 0.0f;
		Camera::DoScreenShake();
		if (!m_pLandPS->IsPlaying())
		{
			m_pLandPS->PlayAtPos(Point2f(m_PhysicsBody.GetPosition().x + m_PhysicsBody.GetShape().width / 2.0f, m_PhysicsBody.GetPosition().y));
		}
		SoundManager::GetInstance()->PlaySound(SoundType::explosion);
	}
}

void BossEnemy::DrawBarrel() const
{
	glPushMatrix();
	glTranslatef
	(
		m_PhysicsBody.GetShape().left + (m_SpriteBody.GetFrameWidth() / 2.0f)
		, m_PhysicsBody.GetShape().bottom + (m_SpriteBody.GetFrameHeight() / 5.0f) * 3.0f
		, 0
	);
	glRotatef(m_BarrelAngle, 0, 0, 1);
	glTranslatef(8.0f, -m_SpriteBarrel.GetFrameHeight() / 2.0f, 0);
	m_SpriteBarrel.Draw();
	glPopMatrix();
}

void BossEnemy::Shoot(const Vector2f& freeVec)
{
	m_ProjectileManager.InstanciateProjectile(freeVec.Normalized() * 100.0f, Point2f(m_PhysicsBody.GetCenter().x, (m_PhysicsBody.GetShape().bottom) + (m_SpriteBody.GetFrameHeight() / 5.0f) * 3.0f) + (freeVec.Normalized() * 12.0f));
	m_LastShotTime = Time::GetInstance()->m_Time;
	SoundManager::GetInstance()->PlaySound(SoundType::cannonShoot);
}

void BossEnemy::UpdateProjectiles(Avatar& playerAvatar, const std::vector<std::vector<Point2f>>& levelVerts)
{
	const Rectf actorShape{ playerAvatar.GetShape() };
	m_ProjectileManager.Update(levelVerts, actorShape);
	if (m_ProjectileManager.HasHitPlayer(actorShape))
	{
		SoundManager::GetInstance()->PlaySound(SoundType::hitHurt);
		playerAvatar.TakeDamage(1);
	}
}