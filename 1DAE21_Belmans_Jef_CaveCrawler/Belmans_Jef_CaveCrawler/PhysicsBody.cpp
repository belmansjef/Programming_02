#include "pch.h"
#include "PhysicsBody.h"
#include "Level.h"
#include "SoundManager.h"
#include "Enums.h"

PhysicsBody::PhysicsBody(float left, float bottom, float width, float height, float initialJumpVelocity)
	: m_Shape { Rectf(left, bottom, width, height) }
	, m_InitialJumpVelocity { initialJumpVelocity }
	, m_HasJumped { false }
{
}

Vector2f& PhysicsBody::Velocity()
{
	return m_Velocity;
}

Rectf& PhysicsBody::Shape()
{
	return m_Shape;
}

Rectf PhysicsBody::GetShape() const
{
	return m_Shape;
}

Point2f PhysicsBody::GetPosition() const
{
	return Point2f(m_Shape.left, m_Shape.bottom);
}

float PhysicsBody::GetTimeSinceGrounded() const
{
	return m_TimeSinceGrounded;
}

bool PhysicsBody::GetIsGrounded() const
{
	return m_IsGrounded;
}

bool PhysicsBody::GetIsMoving() const
{
	return m_IsMoving;
}

void PhysicsBody::SetGravityScale(float gravityScale)
{
	m_GravityScale = gravityScale;
}

void PhysicsBody::SetHasJumped(bool hasJumped)
{
	m_HasJumped = hasJumped;
}

void PhysicsBody::Update(const Level& level)
{
	m_IsGrounded = level.IsOnGround(m_Shape);
	m_IsMoving = !(m_Velocity.x == 0.0f && m_Velocity.y == 0.0f);

	if (m_IsGrounded)
	{
		if (m_TimeSinceGrounded > 0.0f) // Reset velocity when first touching ground
		{
			m_Velocity.y = 0.0f;
		}

		m_TimeSinceGrounded = 0.0f;
	}
	else
	{
		if (m_TimeSinceGrounded >= m_CoyoteTime || m_HasJumped)
		{
			//m_Velocity.y += (m_Gravity * m_GravityScale) * Time::GetInstance()->m_DeltaTime;
		}

		//m_TimeSinceGrounded += Time::GetInstance()->m_DeltaTime;
	}

	ClampVelocity();

	//m_Shape.left += m_Velocity.x * Time::GetInstance()->m_DeltaTime;
	//bottom += m_Velocity.y * Time::GetInstance()->m_DeltaTime;
	level.HandleCollision(m_Shape, m_Velocity);
}

void PhysicsBody::Jump()
{
	if (m_TimeSinceGrounded <= m_CoyoteTime && !m_HasJumped)
	{
		m_Velocity.y = m_InitialJumpVelocity;
		m_GravityScale = 1.0f;

		m_HasJumped = true;

		//SoundManager::GetInstance()->PlaySound(SoundType::jump);
	}	
}

void PhysicsBody::ClampVelocity()
{
	const float currentVelocity{ sqrtf(powf(m_Velocity.x, 2) + powf(m_Velocity.y,2)) };
	if (currentVelocity > m_MaxVelocity)
	{
		float velocityScale{ m_MaxVelocity / currentVelocity };
		m_Velocity *= velocityScale;
	}
}
