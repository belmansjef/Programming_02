#include <iostream>
#include "utils.h"
#include "Avatar.h"

Avatar::Avatar()
	: Avatar(Point2f(), 10.0f, 10.0f, Rectf())
{
}

Avatar::Avatar(const Point2f& center, float width, float height, const Rectf& boundaries)
	: m_Center { center }
	, m_Width { width }
	, m_Height { height }
	, m_PlayerRect
	{
		Rectf
		(
			m_Center.x - m_Width / 2.0f,
			m_Center.y - m_Height / 2.0f,
			m_Width,
			m_Height
		)
	}
	, m_Speed { 250.0f }
	, m_Boundaries{ boundaries }
	, m_Bullet { Bullet(8.0f, 8.0f, boundaries) }
{
}

Avatar::~Avatar()
{
	std::cout << "\"Avatar is kil\"\r\n\"no\"";
}

void Avatar::Update(float elapsedSec, Enemy* pEnemies, int numEnemies)
{
	HandleMoveKeysState(elapsedSec);
	m_Bullet.Update(elapsedSec, pEnemies, numEnemies);
}

void Avatar::Draw() const
{
	utils::SetColor(Color4f(1.0f, 1.0f, 0.0f, 1.0f));
	utils::DrawRect(m_PlayerRect, 4.0f);

	m_Bullet.Draw();
}

void Avatar::SetCenter(const Point2f& center)
{
}

void Avatar::SetDimensions(float width, float height)
{
}

void Avatar::SetBoundaries(const Rectf& boundaries)
{
}

void Avatar::ShootBullet()
{
	m_Center.x = m_PlayerRect.left + m_PlayerRect.width / 2.0f;
	m_Center.y = m_PlayerRect.bottom + m_PlayerRect.height / 2.0f;

	const Vector2f velocity
	{
		0.0f,
		200.0f
	};

	m_Bullet.Shoot(m_Center, velocity);
}

void Avatar::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		ShootBullet();
		break;
	default:
		break;
	}
}

void Avatar::HandleMoveKeysState(float elapsedSec)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT])
	{
		m_PlayerRect.left -= m_Speed * elapsedSec;
		Clamp();
		
	}
	else if (state[SDL_SCANCODE_RIGHT])
	{
		m_PlayerRect.left += m_Speed * elapsedSec;
		Clamp();
		
	}
}

void Avatar::Clamp()
{
	if (m_PlayerRect.left < m_Boundaries.left)
	{
		m_PlayerRect.left = m_Boundaries.left;
	}
	else if (m_PlayerRect.left + m_PlayerRect.width > m_Boundaries.left + m_Boundaries.width)
	{
		m_PlayerRect.left = m_Boundaries.width - m_PlayerRect.width;
	}
}
