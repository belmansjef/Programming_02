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
	const Uint8* state = SDL_GetKeyboardState(NULL);
	bool isGrounded{ level.IsOnGround(m_Shape) };

	switch (m_ActionState)
	{
	case ActionState::waiting:
		
		if ((state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT]) && isGrounded)
		{
			m_ActionState = ActionState::moving;
		}
		break;
	case ActionState::moving:
		m_Velocity += m_Gravity;
		level.HandleCollision(m_Shape, m_Velocity);

		if (state[SDL_SCANCODE_RIGHT])
		{
			m_Velocity.x = m_HorSpeed * elapsedSec;
		}
		else if (state[SDL_SCANCODE_LEFT])
		{
			m_Velocity.x = -m_HorSpeed * elapsedSec;
		}
		else if(isGrounded)
		{
			m_ActionState = ActionState::waiting;
		}

		
		break;
	case ActionState::transforming:
		m_AccuTransformSec += elapsedSec;
		if (m_AccuTransformSec <= m_MaxTransformSec)
		{
			m_Shape.height += 10.0f * elapsedSec;
		}
		else
		{
			m_AccuTransformSec = 0.0f;
			m_ActionState = ActionState::waiting;
		}
		break;
	default:
		break;
	}

	
}

void Avatar::Draw() const
{
	switch (m_ActionState)
	{
	case ActionState::waiting:
		utils::SetColor(Color4f(1.0f, 1.0f, 0.0f, 1.0f));
		break;
	case ActionState::moving:
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case ActionState::transforming:
		utils::SetColor(Color4f(1.0f, 0.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}

	utils::FillRect(m_Shape);
}

void Avatar::PowerUpHit()
{
	m_ActionState = ActionState::transforming;
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}
