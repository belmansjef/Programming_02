#include <iostream>
#include "pch.h"
#include "Avatar.h"
#include "Texture.h"
#include "Level.h"

Avatar::Avatar()
	: m_pSpritesTexture{ new Texture("Resources/Images/AvatarSheet.png") }
{
}

Avatar::Avatar(const Avatar& other)
	: m_pSpritesTexture { new Texture("Resources/Images/AvatarSheet.png")}
	, m_Velocity { other.m_Velocity }
	, m_AnimFrame { other.m_AnimFrame }
	, m_AnimTime { other.m_AnimTime }
	, m_Power { other.m_Power }
{
}

Avatar::~Avatar()
{
	delete m_pSpritesTexture;
	m_pSpritesTexture = nullptr;
}

Avatar& Avatar::operator=(const Avatar& other)
{
	m_pSpritesTexture = new Texture("Resources/Images/AvatarSheet.png");
	m_Velocity = other.m_Velocity;
	m_AnimFrame = other.m_AnimFrame;
	m_AnimTime = other.m_AnimTime;
	m_Power = other.m_Power;

	return *this;
}

void Avatar::Update(float elapsedSec, const Level& level)
{
	switch (m_ActionState)
	{
	case ActionState::waiting:
		UpdateWaitingState();
		break;
	case ActionState::moving:
		UpdateMovingState(elapsedSec, level);
		break;
	case ActionState::transforming:
		UpdateTransformingState(elapsedSec);
		break;
	default:
		break;
	}

	UpdateAnimation(elapsedSec);
}

void Avatar::Draw() const
{
	// Draw avatar
	const Rectf clipRect
	{
		m_ClipWidth * m_AnimFrame,
		m_pSpritesTexture->GetHeight() + (m_ClipHeight * (int(m_ActionState) + (m_Power * 3) + 1)),
		m_ClipWidth,
		m_ClipHeight
	};

	glPushMatrix();
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		if (m_Velocity.x < 0.0f)
		{
			glScalef(-1, 1, 1);
			glTranslatef(-m_Shape.width, 0, 0);
		}
		m_pSpritesTexture->Draw(Point2f(), clipRect);
	glPopMatrix();
}

void Avatar::PowerUpHit()
{
	m_ActionState = ActionState::transforming;
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}

void Avatar::UpdateWaitingState()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_UP])
	{
		m_ActionState = ActionState::moving;
	}
}

void Avatar::UpdateMovingState(float elapsedSec, const Level& level)
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	bool isGrounded{ level.IsOnGround(m_Shape, m_Velocity) };

	if (isGrounded)
	{
		m_GravityScale = 1.0f;
		m_Velocity.x = state[SDL_SCANCODE_RIGHT] * m_MovementSpeed + state[SDL_SCANCODE_LEFT] * -m_MovementSpeed;
		m_Velocity.y = state[SDL_SCANCODE_UP] * m_InitialJumpVelocity;
	}

	if (!isGrounded)
	{
		if (!state[SDL_SCANCODE_UP] || m_Velocity.y < 0.0f)
		{
			m_GravityScale = 3.0f;
		}
		m_Velocity.y += m_Gravity * m_GravityScale * elapsedSec;
	}
	else if (m_Velocity.x == 0.0f)
	{
		m_ActionState = ActionState::waiting;
	}

	DampVelocity(elapsedSec);
	ClampVelocity();
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;

	level.HandleCollision(m_Shape, m_Velocity);
}

void Avatar::UpdateTransformingState(float elapsedSec)
{
	m_AccuTransformSec += elapsedSec;
	if(m_AccuTransformSec >= m_MaxTransformSec)
	{
		m_AccuTransformSec = 0.0f;
		++m_Power;
		m_ActionState = ActionState::moving;
	}
}

void Avatar::UpdateAnimation(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime >= 1.0f / m_NrFramesPerSec)
	{
		m_AnimFrame++;
		m_AnimTime = 0.0f;
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
