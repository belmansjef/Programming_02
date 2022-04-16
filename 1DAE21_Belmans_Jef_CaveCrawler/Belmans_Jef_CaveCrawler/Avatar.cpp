#include <iostream>
#include "pch.h"
#include "Avatar.h"
#include "Texture.h"
#include "Level.h"
#include "Game.h"

Avatar::Avatar(float left, float bottom, float width, float height)
	: m_StartPos { Point2f(left, bottom) }
	, m_Sprite { Sprite(SpriteType::player) }
	, m_Pb { PhysicsBody(left, bottom, width, height, 150.0f) }
	, m_Gun { Gun() }
{ 
}

ProjectileManager& Avatar::GetProjectileManager()
{
	return m_Gun.GetProjectileManager();
}

bool Avatar::GetIsDead() const
{
	return m_AvatarHealth.GetIsDead();
}

bool Avatar::ShouldTrack()
{
	m_ShouldTrack |= abs(m_StandStillPos.x - m_Pb.GetPosition().x) > m_HorCamDeadZone;
	return m_ShouldTrack;
}

Rectf Avatar::GetShape() const
{
	return m_Pb.GetShape();
}

Health& Avatar::GetHealth()
{
	return m_AvatarHealth;
}

void Avatar::OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		m_Gun.Shoot(m_Pb.Shape(), int(m_HorizontalScale));
		break;
	default:
		break;
	}
}

void Avatar::Update(const Level& level)
{
	GetInput();
	ProcessInput(level);
	m_Pb.Update(level);
	m_Sprite.Update();
	m_Gun.Update(level.GetLevelVerts());
}

void Avatar::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Pb.GetPosition().x, m_Pb.GetPosition().y, 0);
		glScalef(m_HorizontalScale, 1, 1);
		if (m_HorizontalScale < 0)
			glTranslatef(-m_Pb.GetShape().width, 0, 0);
		m_Sprite.Draw();
	glPopMatrix();

	m_Gun.Draw();
}

void Avatar::Reset()
{
	m_Pb.Shape().left = m_StartPos.x;
	m_Pb.Shape().bottom = m_StartPos.y;
	m_AvatarHealth.Heal(m_MaxHealth);
	m_Gun.GetProjectileManager().Reset();
}

void Avatar::GetInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	m_MovementDirection = state[SDL_SCANCODE_D] - state[SDL_SCANCODE_A];
	m_IsPressingJump = bool(state[SDL_SCANCODE_SPACE]);
}

void Avatar::ProcessInput(const Level& level)
{
	if (m_MovementDirection < 0)
	{
		m_HorizontalScale = -1;
	}
	else if (m_MovementDirection > 0)
	{
		m_HorizontalScale = 1;
	}

	m_Pb.Velocity().x = m_MovementDirection* m_MovementSpeed;;
	if (m_IsPressingJump)
	{
		m_Pb.Jump();
	}

	if (m_ShouldTrack)
	{
		if (!m_Pb.GetIsMoving())
		{
			m_TimeSinceLastMoved += Time::deltaTime;
		}
		else
		{
			m_TimeSinceLastMoved = 0.0f;
		}
	}

	if (m_TimeSinceLastMoved >= m_StandStillDetectionTime)
	{
		m_StandStillPos.x = m_Pb.GetPosition().x;
		m_StandStillPos.y = m_Pb.GetPosition().y;
		m_TimeSinceLastMoved = 0.0f;
		m_ShouldTrack = false;
	}

	if (m_Pb.GetIsGrounded())
	{
		m_Pb.SetHasJumped(m_IsPressingJump);
	}

	SetAnimation();
	SetGravityScale();
}

void Avatar::SetAnimation()
{
	if (m_Pb.GetIsGrounded())
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
		if (!m_IsPressingJump || m_Pb.Velocity().y < 0.0f)
		{
			m_Sprite.SetAnimation("jump_down");
		}
	}
}

void Avatar::SetGravityScale()
{
	if (m_Pb.GetIsGrounded())
	{
		m_Pb.SetGravityScale(1.0f);
	}
	else if (m_Pb.Velocity().y <= 0.0f || !m_IsPressingJump)
	{
		m_Pb.SetGravityScale(4.0f);
	}
}
