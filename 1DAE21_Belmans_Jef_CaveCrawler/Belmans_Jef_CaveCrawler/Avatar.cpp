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
	GetInput();
	ProcessInput(elapsedSec, level);
	m_Sprite.Update(elapsedSec);
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

void Avatar::PowerUpHit()
{
	
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}

//void Avatar::UpdateIdleState()
//{
//	const Uint8* state = SDL_GetKeyboardState(NULL);
//	if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_UP])
//	{
//		m_Sprite.SetAnimation("run");
//		m_ActionState = ActionState::moving;
//	}
//}
//
//void Avatar::UpdateMovingState(float elapsedSec, const Level& level)
//{
//	const Uint8* state = SDL_GetKeyboardState(NULL);
//	bool isGrounded{ level.IsOnGround(m_Shape) };
//
//	if (isGrounded)
//	{
//		m_GravityScale = 1.0f;
//		m_Velocity.x = state[SDL_SCANCODE_RIGHT] * m_MovementSpeed + state[SDL_SCANCODE_LEFT] * -m_MovementSpeed;
//		m_Velocity.y = state[SDL_SCANCODE_UP] * m_InitialJumpVelocity;
//	}
//
//	if (!isGrounded)
//	{
//		m_Sprite.SetAnimation("jumpup");
//		m_ActionState = ActionState::jumping;
//	}
//	else if (m_Velocity.x == 0.0f)
//	{
//		m_Sprite.SetAnimation("idle");
//		m_ActionState = ActionState::idle;
//	}
//
//	DampVelocity(elapsedSec);
//	ClampVelocity();
//	m_Shape.left += m_Velocity.x * elapsedSec;
//	m_Shape.bottom += m_Velocity.y * elapsedSec;
//
//	level.HandleCollision(m_Shape, m_Velocity);
//}
//
//void Avatar::UpdateJumpingState(float elapsedSec, const Level& level)
//{
//	bool isGrounded{ level.IsOnGround(m_Shape) };
//	const Uint8* state = SDL_GetKeyboardState(NULL);
//
//	if (!state[SDL_SCANCODE_UP] || m_Velocity.y < 0.0f)
//	{
//		m_GravityScale = 3.0f;
//	}
//
//	m_Velocity.y += m_Gravity * m_GravityScale * elapsedSec;
//
//	DampVelocity(elapsedSec);
//	ClampVelocity();
//	m_Shape.left += m_Velocity.x * elapsedSec;
//	m_Shape.bottom += m_Velocity.y * elapsedSec;
//
//	level.HandleCollision(m_Shape, m_Velocity);
//
//	if (isGrounded)
//	{
//		m_Sprite.SetAnimation("run");
//		m_ActionState = ActionState::idle;
//	}
//
//	if(m_Velocity.y < 0.0f)
//	{
//		m_Sprite.SetAnimation("jumpdown");
//	}
//
//	
//}

void Avatar::GetInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	m_MovementDirection = state[SDL_SCANCODE_D] - state[SDL_SCANCODE_A];
	m_JumpInput = state[SDL_SCANCODE_SPACE];
}

void Avatar::ProcessInput(float elapsedSec, const Level& level)
{
	bool isGrounded{ level.IsOnGround(m_Shape) };

	if (m_MovementDirection < 0)
	{
		m_HorizontalScale = -1;
	}
	else if (m_MovementDirection > 0)
	{
		m_HorizontalScale = 1;
	}

	m_Velocity.x = m_MovementDirection * m_MovementSpeed;

	if (isGrounded)
	{
		if (m_MovementDirection != 0)
		{
			m_Sprite.SetAnimation("run");
		}
		else
		{
			m_Sprite.SetAnimation("idle");
		}

		m_Velocity.y = m_InitialJumpVelocity * m_JumpInput;
		m_GravityScale = 1.0f;
	}
	else
	{
		m_Sprite.SetAnimation("jump_up");
		if (m_JumpInput == 0 || m_Velocity.y < 0.0f)
		{
			m_GravityScale = 3.0f;
			m_Sprite.SetAnimation("jump_down");
		}
		m_Velocity.y += (m_Gravity * m_GravityScale) * elapsedSec;
	}

	ClampVelocity();
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;

	level.HandleCollision(m_Shape, m_Velocity);
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
	m_Velocity = m_Velocity / (1 + m_Damping * elapsedSec);
}
