#include "Enemy.h"
#include <iostream>
#include "utils.h"

Enemy::Enemy()
	: Enemy(Point2f(), 10.0f, 10.0f)
{
	std::cout << "Default enemy created!\r\n";
}

Enemy::Enemy(const Point2f& center, float width, float height)
	: m_Center { center }
	, m_Width { width }
	, m_Height { height }
	, m_EnemyRect {
	Rectf
	(
		m_Center.x - m_Width / 2.0f,
		m_Center.y - m_Height / 2.0f,
		m_Width,
		m_Height
	)}
	, m_IsDead { false }
{
	std::cout << "Enemy created at: [" << m_Center.x << ", " << m_Center.y <<
		"] with width: " << m_Width << " and height: " << m_Height << "!\r\n";
}

Enemy::~Enemy()
{
	std::cout << "Deleted enemy: " << this << std::endl;
}

void Enemy::Draw() const
{
	utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	utils::DrawRect(m_EnemyRect, 4.0f);
}

bool Enemy::DoHitTest(const Rectf& other) const
{
	return utils::IsOverlapping(m_EnemyRect, other);
}

bool Enemy::IsDead() const
{
	return m_IsDead;
}

void Enemy::SetCenter(const Point2f& center)
{
	m_Center = center;
}

void Enemy::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}
