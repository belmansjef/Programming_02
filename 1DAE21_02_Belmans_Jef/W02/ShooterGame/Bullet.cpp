#include "Bullet.h"
#include "Enemy.h"
#include "utils.h"

Bullet::Bullet()
	: Bullet(10.0f, 40.0f, Rectf())
{
}

Bullet::Bullet(float width, float height, const Rectf& boundaries)
	: m_Center { Point2f() }
	, m_Width { width }
	, m_Height { height }
	, m_Velocity { Vector2f() }
	, m_BulletRect
	{
		Rectf
		(
			m_Center.x - m_Width / 2.0f,
			m_Center.y - m_Height / 2.0f,
			m_Width,
			m_Height
		)
	}
	, m_Boundaries{ boundaries }
	, m_IsActivated{ false }
{
}

void Bullet::Draw() const
{
	if (!m_IsActivated) return;

	utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	utils::FillRect(m_BulletRect);
}

void Bullet::Update(float elapsedSec, Enemy* pEnemies, int numEnemies)
{
	if (!m_IsActivated) return;

	m_BulletRect.bottom += m_Velocity.y * elapsedSec;
	CheckEnemiesHit(pEnemies, numEnemies);
	CheckBoundaries();
}

void Bullet::Shoot(const Point2f& center, const Vector2f velocity)
{
	if (m_IsActivated) return;

	m_Center = center;
	m_Velocity = velocity;

	m_BulletRect.left = m_Center.x - m_Width / 2.0f;
	m_BulletRect.bottom = m_Center.y - m_Height / 2.0f;

	m_IsActivated = true;
}

void Bullet::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Bullet::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

void Bullet::CheckBoundaries()
{
	if (m_BulletRect.bottom >= m_Boundaries.height)
	{
		m_IsActivated = false;
	}
}

void Bullet::CheckEnemiesHit(Enemy* pEnemies, int numEnemies)
{
	for (int i = 0; i < numEnemies; i++)
	{
		if (pEnemies[i].DoHitTest(m_BulletRect))
		{
			std::cout << "Hit!\r\n";
			delete &pEnemies[i];
			m_IsActivated = false;
		}
	}
}
