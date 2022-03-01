#include "pch.h"
#include "Avatar.h"
#include "Level.h"

Avatar::Avatar()
{
}

Avatar::~Avatar()
{
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
}

void Avatar::Draw() const
{
	// Draw avatar
	switch (m_ActionState)
	{
	case ActionState::waiting:
		utils::SetColor(Color4f(1.0f, 1.0f, 0.0f, 1.0f));
		break;
	case ActionState::moving:
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case ActionState::transforming:
		utils::SetColor(Color4f(0.0f, 1.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}
	utils::FillRect(m_Shape);

	// Draw power
	utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
	for (size_t i = 0; i < m_Power; i++)
	{
		const Rectf powerRect
		{
			m_Shape.left + 2.0f + (7.0f * i),
			m_Shape.bottom + 2.0f,
			5.0f,
			5.0f,
		};

		utils::FillRect(powerRect);
	}
}

void Avatar::PowerUpHit()
{
	++m_Power;
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
	const Uint8* state = SDL_GetKeyboardState(NULL);
	bool isGrounded{ level.IsOnGround(m_Shape) };

	if (isGrounded)
	{
		m_Velocity.x = state[SDL_SCANCODE_RIGHT] * m_HorSpeed + state[SDL_SCANCODE_LEFT] * -m_HorSpeed;
		m_Velocity.y = state[SDL_SCANCODE_UP] * m_JumpSpeed;
	}

	if (!isGrounded)
	{
		m_Velocity.y += m_Gravity.y * elapsedSec;
	}
	else if (m_Velocity.x == 0.0f)
	{
		m_ActionState = ActionState::waiting;
	}

	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
	level.HandleCollision(m_Shape, m_Velocity);
}

void Avatar::UpdateTransformingState(float elapsedSec)
{
	m_AccuTransformSec += elapsedSec;
	if (m_AccuTransformSec <= m_MaxTransformSec)
	{
		m_Shape.height += 15.0f * elapsedSec;
	}
	else
	{
		m_AccuTransformSec = 0.0f;
		m_ActionState = ActionState::moving;
	}
}
