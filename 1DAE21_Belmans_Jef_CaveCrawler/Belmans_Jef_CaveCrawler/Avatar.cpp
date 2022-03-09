#include <iostream>
#include "pch.h"
#include "Avatar.h"
#include "Texture.h"
#include "Level.h"

Avatar::Avatar()
	: m_Sprite { Sprite(Sprite::SpriteType::player) }
{
}

Avatar::~Avatar()
{
}

void Avatar::Update(float elapsedSec, const Level& level)
{
	switch (m_ActionState)
	{
	case ActionState::idle:
		UpdateIdleState();
		break;
	case ActionState::moving:
		UpdateMovingState(elapsedSec, level);
		break;
	case ActionState::jumping:
		UpdateJumpingState(elapsedSec, level);
		break;
	default:
		break;
	}

	m_Sprite.Update(elapsedSec);
}

void Avatar::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		glScalef(5, 5, 1);
		if (m_Velocity.x < 0.0f)
		{
			glScalef(-1, 1, 1);
			glTranslatef(-m_Shape.width, 0, 0);
		}
		m_Sprite.Draw();
	glPopMatrix();
}

void Avatar::PowerUpHit()
{
	
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}

void Avatar::UpdateIdleState()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_UP])
	{
		m_Sprite.SetAnimation("run");
		m_ActionState = ActionState::moving;
	}
}

void Avatar::UpdateMovingState(float elapsedSec, const Level& level)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	bool isGrounded{ level.IsOnGround(m_Shape) };

	if (isGrounded)
	{
		m_GravityScale = 1.0f;
		m_Velocity.x = state[SDL_SCANCODE_RIGHT] * m_MovementSpeed + state[SDL_SCANCODE_LEFT] * -m_MovementSpeed;
		m_Velocity.y = state[SDL_SCANCODE_UP] * m_InitialJumpVelocity;
	}

	if (!isGrounded)
	{
		m_Sprite.SetAnimation("jumpup");
		m_ActionState = ActionState::jumping;
	}
	else if (m_Velocity.x == 0.0f)
	{
		m_Sprite.SetAnimation("idle");
		m_ActionState = ActionState::idle;
	}

	DampVelocity(elapsedSec);
	ClampVelocity();
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;

	level.HandleCollision(m_Shape, m_Velocity);
}

void Avatar::UpdateJumpingState(float elapsedSec, const Level& level)
{
	bool isGrounded{ level.IsOnGround(m_Shape) };
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (!state[SDL_SCANCODE_UP] || m_Velocity.y < 0.0f)
	{
		m_GravityScale = 3.0f;
	}

	m_Velocity.y += m_Gravity * m_GravityScale * elapsedSec;

	DampVelocity(elapsedSec);
	ClampVelocity();
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;

	level.HandleCollision(m_Shape, m_Velocity);

	if (isGrounded)
	{
		m_Sprite.SetAnimation("run");
		m_ActionState = ActionState::idle;
	}

	if(m_Velocity.y < 0.0f)
	{
		m_Sprite.SetAnimation("jumpdown");
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

void Avatar::DampVelocity(float elapsedSec)
{
	m_Velocity /= 1 + m_Damping * elapsedSec;
}
