#include "BossEnemy.h"
#include "pch.h"
#include "Time.h"
#include "Enums.h"
#include "Avatar.h"
#include "ParticleSystem.h"

BossEnemy::BossEnemy(float left, float bottom)
	: m_StartPos{ left, bottom }
	, m_Sprite { SpriteType::boss }
	, m_PhysicsBody{ left, bottom, m_Sprite.GetFrameWidth(), m_Sprite.GetFrameHeight(), 175.0f}
	, m_Health { m_MaxHealth, &m_Sprite, 0.0f }
	, m_MovementDirection { 1 }
	, m_TimeSinceGrounded{ 0.0f }
	, m_CurrentState { BossState::landed }
	, m_pDeathPS{ new ParticleSystem(15) }
{
	m_pDeathPS->Initialize(Point2f(-20.0f, -20.0f), Point2f{ 20.0f, 20.0f }, Point2f(2.0f, 3.0f), Point2f(0.1f, 0.1f), Point2f(1.5f, 2.5f));
}

BossEnemy::~BossEnemy()
{
	delete m_pDeathPS;
	m_pDeathPS = nullptr;
}

bool BossEnemy::IsOverlapping(const Rectf& otherShape) const
{
	return utils::IsOverlapping(otherShape, m_PhysicsBody.GetShape());
}

bool BossEnemy::IsDead() const
{
	return m_Health.GetIsDead();
}

Rectf BossEnemy::GetBoxCollider() const
{
	return m_PhysicsBody.GetShape();
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

	m_Sprite.SetAnimation("landed");
	m_CurrentState = BossState::landed;
	m_MovementDirection = 1;
	m_TimeSinceGrounded = Time::GetInstance()->m_Time;
}

void BossEnemy::Update(const Avatar& playerAvatar, const Level& level)
{
	if (!IsDead())
	{
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
		m_Sprite.Update();
	}
	
	m_pDeathPS->Update();
}

void BossEnemy::Draw() const
{
	if (!IsDead())
	{
		glPushMatrix();
			glTranslatef(m_PhysicsBody.GetPosition().x, m_PhysicsBody.GetPosition().y, 0);
			m_Sprite.Draw();
		glPopMatrix();
	}
	
	m_pDeathPS->Draw();
}

void BossEnemy::SetState()
{
	if (Time::GetInstance()->m_Time >= m_TimeSinceGrounded + m_StandTime && m_CurrentState == BossState::landed)
	{
		m_CurrentState = BossState::pre_charge;
		m_Sprite.SetAnimation("pre_charge");
	}
	else if (Time::GetInstance()->m_Time >= m_TimeSinceGrounded + m_StandTime + m_PreChargeTime && m_CurrentState == BossState::pre_charge)
	{
		m_CurrentState = BossState::charge;
		m_Sprite.SetAnimation("charge");
	}
	else if (Time::GetInstance()->m_Time >= m_TimeSinceGrounded + m_StandTime + m_PreChargeTime + m_ChargeTime && m_CurrentState == BossState::charge)
	{
		m_PhysicsBody.Jump();
		m_CurrentState = BossState::in_air;
		m_Sprite.SetAnimation("in_air");
		m_PhysicsBody.Velocity().x = m_HorizontalMovementSpeed * m_MovementDirection;
	}

	if (m_PhysicsBody.GetIsGrounded() && m_CurrentState == BossState::in_air && Time::GetInstance()->m_Time >= m_TimeSinceGrounded + m_StandTime + m_PreChargeTime + m_ChargeTime + 1.0f)
	{
		m_TimeSinceGrounded = Time::GetInstance()->m_Time;
		m_CurrentState = BossState::landed;
		m_Sprite.SetAnimation("landed");
		m_PhysicsBody.SetHasJumped(false);
		m_PhysicsBody.Velocity().x = 0.0f;
	}
}