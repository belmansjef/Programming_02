#include "BossEnemy.h"
#include "pch.h"
#include "Time.h"
#include "Enums.h"
#include "Avatar.h"

BossEnemy::BossEnemy(float left, float bottom)
	: m_StartPos{ left, bottom }
	, m_Sprite { SpriteType::boss }
	, m_PhysicsBody{ left, bottom, m_Sprite.GetFrameWidth(), m_Sprite.GetFrameHeight(), 175.0f}
	, m_Health { m_MaxHealth, &m_Sprite, 0.5f }
	, m_MovementDirection { 1 }
	, m_TimeSinceGrounded{ 0.0f }
	, m_CurrentState { BossState::landed }
{
}

void BossEnemy::Update(const Level& level, const Avatar& playerAvatar)
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

void BossEnemy::Draw() const
{
	glPushMatrix();
		glTranslatef(m_PhysicsBody.GetPosition().x, m_PhysicsBody.GetPosition().y, 0);
		m_Sprite.Draw();
	glPopMatrix();
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