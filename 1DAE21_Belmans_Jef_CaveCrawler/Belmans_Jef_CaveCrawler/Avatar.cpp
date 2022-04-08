#include <iostream>
#include "pch.h"
#include "Avatar.h"
#include "Texture.h"
#include "Level.h"
#include "Game.h"

Avatar::Avatar(float left, float bottom, float width, float height, int maxhealth)
	: m_Sprite { Sprite(SpriteType::player) }
	, m_Shape{ Rectf(left, bottom, width, height) }
	, m_AvatarHealth{ Health(maxhealth) }
	, m_Gun { Gun() }
{
}

void Avatar::Update(const Level& level)
{
	GetInput();
	ProcessInput(level);
	m_Sprite.Update();
}

void Avatar::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		glScalef(m_HorizontalScale, 1, 1);
		if (m_HorizontalScale < 0)
		{
			glTranslatef(-m_Shape.width, 0, 0);
		}
		m_Sprite.Draw();
	glPopMatrix();
}

bool Avatar::ShouldTrack() const
{
	return abs(m_StandStillPos.x - m_Shape.left) > m_HorCamDeadZone || m_IsMoving;
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}

Health& Avatar::GetHealth()
{
	return m_AvatarHealth;
}

void Avatar::GetInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	m_MovementDirection = state[SDL_SCANCODE_D] - state[SDL_SCANCODE_A];
	m_IsPressingJump = bool(state[SDL_SCANCODE_SPACE]);
	m_IsPressingShoot = bool(state[SDL_SCANCODE_LCTRL]);
}

void Avatar::ProcessInput(const Level& level)
{
	if (m_IsPressingShoot)
	{
		m_Gun.Shoot(m_Shape);
	}

	m_IsGrounded = level.IsOnGround(m_Shape);

	if (m_MovementDirection < 0)
	{
		m_HorizontalScale = -1;
	}
	else if (m_MovementDirection > 0)
	{
		m_HorizontalScale = 1;
	}

	Jump();
	SetAnimation();
	SetGravityScale();

	m_Velocity.x = m_MovementDirection * m_MovementSpeed;

	m_IsMoving |= (m_Velocity.x == 0.0f && m_Velocity.y == 0.0f && ShouldTrack());

	if (m_IsMoving)
	{
		if (m_Velocity.x == 0.0f && m_Velocity.y == 0.0f)
		{
			m_TimeSinceMovement += Time::deltaTime;
		}
		else
		{
			m_TimeSinceMovement = 0.0f;
		}
	}

	if (abs(m_Velocity.x) <= 0.01f && m_TimeSinceMovement >= m_StandStillDetectionTime)
	{
		m_StandStillPos.x = m_Shape.left;
		m_StandStillPos.y = m_Shape.bottom;
		m_TimeSinceMovement = 0.0f;
		m_IsMoving = false;
	}

	if (m_IsGrounded)
	{
		if (m_TimeSinceGrounded > 0.0f) // Reset velocity when first touching ground
		{
			m_Velocity.y = 0.0f;
		}

		m_HasJumped = m_IsPressingJump;
		m_TimeSinceGrounded = 0.0f;
	}
	else
	{
		if (m_TimeSinceGrounded >= m_CoyoteTime || m_HasJumped)
		{
			m_Velocity.y += (m_Gravity * m_GravityScale) * Time::deltaTime;
		}
		
		m_TimeSinceGrounded += Time::deltaTime;
	}

	ClampVelocity();
	m_Shape.left += m_Velocity.x * Time::deltaTime;
	m_Shape.bottom += m_Velocity.y * Time::deltaTime;

	level.HandleCollision(m_Shape, m_Velocity);
}

void Avatar::Jump()
{
	if ((m_IsPressingJump && !m_HasJumped) && m_TimeSinceGrounded <= m_CoyoteTime)
	{
		m_Velocity.y = m_InitialJumpVelocity;
		m_GravityScale = 1.0f;
		m_HasJumped = true;
	}
}

void Avatar::SetAnimation()
{
	if (m_IsGrounded)
	{
		if (m_MovementDirection != 0)
		{
			m_Sprite.SetAnimation("run");
		}
		else
		{
			m_Sprite.SetAnimation("idle");
		}
	}
	else
	{
		m_Sprite.SetAnimation("jump_up");
		if (!m_IsPressingJump || m_Velocity.y < 0.0f)
		{
			m_Sprite.SetAnimation("jump_down");
		}
	}
}

void Avatar::SetGravityScale()
{
	if (m_IsGrounded)
	{
		m_GravityScale = 1.0f;
	}
	else if (m_Velocity.y <= 0.0f || !m_IsPressingJump)
	{
		m_GravityScale = 4.5f;
	}
}

void Avatar::ClampVelocity()
{
	const float currentVelocity{ sqrtf(powf(m_Velocity.x, 2) + powf(m_Velocity.y,2)) };
	if (currentVelocity > m_MaxVelocity)
	{
		float velocityScale{ m_MaxVelocity / currentVelocity };
		m_Velocity *= velocityScale;
	}
}

void Avatar::DampVelocity()
{
	m_Velocity = m_Velocity / (1 + m_Damping * Time::deltaTime);
}
