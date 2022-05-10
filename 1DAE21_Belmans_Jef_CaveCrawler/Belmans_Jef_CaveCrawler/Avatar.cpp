#include <iostream>
#include "pch.h"
#include "Avatar.h"
#include "Texture.h"
#include "Level.h"
#include "Game.h"

Avatar::Avatar(float left, float bottom, float width, float height)
	: m_StartPos { Point2f(left, bottom) }
	, m_PhysicsBody { PhysicsBody(left, bottom, width, height, 150.0f) }
	, m_Gun { Gun() }
	, m_Sprite{ Sprite(SpriteType::player) }	
	, m_AvatarHealth{ Health(m_MaxHealth, &m_Sprite, 1.0f, true) }
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

void Avatar::TakeDamage(int damage)
{
	m_AvatarHealth.TakeDamage(damage);
}

void Avatar::Heal(int value)
{
	m_AvatarHealth.Heal(value);
}

bool Avatar::ShouldTrack()
{
	m_ShouldTrack |= abs(m_StandStillPos.x - m_PhysicsBody.GetPosition().x) > m_HorCamDeadZone;
	return m_ShouldTrack;
}

Rectf Avatar::GetShape() const
{
	if (m_AvatarHealth.GetIsDead())
	{
		return Rectf();
	}
	return m_PhysicsBody.GetShape();
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
		m_Gun.Shoot(m_PhysicsBody.GetPosition(), int(m_HorizontalScale));
		break;
	default:
		break;
	}
}

void Avatar::Update(const Level& level, const GameState& state)
{
	if (state == GameState::InGame)
	{
		GetInput();
	}
	
	ProcessInput(level);
	m_PhysicsBody.Update(level);
	m_Sprite.Update();
	m_Gun.Update(level.GetLevelVerts());
}

void Avatar::Draw() const
{
	if (m_AvatarHealth.GetIsDead()) return;

	glPushMatrix();
		glTranslatef(m_PhysicsBody.GetPosition().x, m_PhysicsBody.GetPosition().y, 0);
		glScalef(m_HorizontalScale, 1, 1);
		if (m_HorizontalScale < 0)
			glTranslatef(-m_PhysicsBody.GetShape().width, 0, 0);
		m_Sprite.Draw();
	glPopMatrix();

	m_Gun.Draw();
}

void Avatar::Reset()
{
	m_HorizontalScale = 1;

	m_PhysicsBody.Shape().left = m_StartPos.x;
	m_PhysicsBody.Shape().bottom = m_StartPos.y;
	m_PhysicsBody.Velocity() = Vector2f();

	m_MovementDirection = 0;
	m_IsPressingJump = false;
	m_IsPressingShoot = false;

	m_Sprite.SetAnimation("idle");

	m_AvatarHealth.Heal(m_MaxHealth);
	m_Gun.GetProjectileManager().Reset();
}

void Avatar::GetInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	m_MovementDirection = state[SDL_SCANCODE_D] - state[SDL_SCANCODE_A];
	m_IsPressingJump = bool(state[SDL_SCANCODE_SPACE]);
	m_IsPressingShoot = bool(state[SDL_SCANCODE_RCTRL]);
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

	m_PhysicsBody.Velocity().x = m_MovementDirection* m_MovementSpeed;;
	if (m_IsPressingJump)
	{
		m_PhysicsBody.Jump();
	}

	if (m_ShouldTrack)
	{
		if (!m_PhysicsBody.GetIsMoving())
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
		m_StandStillPos.x = m_PhysicsBody.GetPosition().x;
		m_StandStillPos.y = m_PhysicsBody.GetPosition().y;
		m_TimeSinceLastMoved = 0.0f;
		m_ShouldTrack = false;
	}

	if (m_PhysicsBody.GetIsGrounded())
	{
		m_PhysicsBody.SetHasJumped(m_IsPressingJump);
	}

	if (m_IsPressingShoot)
	{
		m_Gun.Shoot(m_PhysicsBody.GetPosition(), int(m_HorizontalScale));
	}

	SetAnimation();
	SetGravityScale();
}

void Avatar::SetAnimation()
{
	if (m_PhysicsBody.GetIsGrounded())
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
		if (!m_IsPressingJump || m_PhysicsBody.Velocity().y < 0.0f)
		{
			m_Sprite.SetAnimation("jump_down");
		}
	}
}

void Avatar::SetGravityScale()
{
	if (m_PhysicsBody.GetIsGrounded())
	{
		m_PhysicsBody.SetGravityScale(1.0f);
	}
	else if (m_PhysicsBody.Velocity().y <= 0.0f || !m_IsPressingJump)
	{
		m_PhysicsBody.SetGravityScale(4.0f);
	}
}
