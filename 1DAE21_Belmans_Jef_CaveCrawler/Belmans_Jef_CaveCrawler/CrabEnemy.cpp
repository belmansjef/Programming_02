#include "pch.h"
#include "CrabEnemy.h"
#include "Level.h"
#include "Sprite.h"
#include "SoundManager.h"

CrabEnemy::CrabEnemy(float left, float bottom, float width, float height, int movementDirection, int maxHealth)
	: m_Health { Health(maxHealth, &m_Sprite, 0.1f) }
	, m_MaxHealth { maxHealth }
	, m_PhysicsBody { left, bottom, width, height }
	, m_MovementDirection { movementDirection }
	, m_Sprite { Sprite(SpriteType::crabEnemy) }
	, m_StartPos { left, bottom }
{
}

Rectf CrabEnemy::GetBoxCollider() const
{
	return m_PhysicsBody.GetShape();
}

bool CrabEnemy::IsOverlapping(const Rectf& shape) const
{
	return utils::IsOverlapping(m_PhysicsBody.GetShape(), shape);
}

bool CrabEnemy::IsDead() const
{
	return m_Health.GetIsDead();
}

void CrabEnemy::TakeDamage(int damage)
{
	m_Health.TakeDamage(damage);
}

void CrabEnemy::Update(const Level& level)
{
	m_PhysicsBody.Velocity().x = m_MovementDirection * m_MovementSpeed;
	m_PhysicsBody.Update(level);
	DoCollisionCheck(level.GetLevelVerts());

	m_Sprite.Update();
}

void CrabEnemy::Draw() const
{
	glPushMatrix();
		glTranslatef(m_PhysicsBody.GetPosition().x, m_PhysicsBody.GetPosition().y, 0);
		m_Sprite.Draw();
	glPopMatrix();
}

void CrabEnemy::Reset()
{
	m_Health.Heal(m_MaxHealth);
	m_PhysicsBody.Shape().left = m_StartPos.x;
	m_PhysicsBody.Shape().bottom = m_StartPos.y;
	m_MovementDirection = 1;
}

void CrabEnemy::DoCollisionCheck(const std::vector<std::vector<Point2f>>& levelVerts)
{
	utils::HitInfo hitInfo;
	const Point2f center
	{
		m_PhysicsBody.GetPosition().x + m_PhysicsBody.GetShape().width / 4.0f,
		m_PhysicsBody.GetPosition().y + m_PhysicsBody.GetShape().height / 2.0f
	};

	const Point2f right
	{
		m_PhysicsBody.GetPosition().x + m_PhysicsBody.GetShape().width,
		center.y
	};

	const Point2f left
	{
		m_PhysicsBody.GetPosition().x,
		center.y
	};

	for (std::vector<Point2f> verts : levelVerts)
	{
		if (utils::Raycast(verts, center, right, hitInfo))
		{
			m_MovementDirection = -1;
		}
		else if (utils::Raycast(verts, center, left, hitInfo))
		{
			m_MovementDirection = 1;
		}
	}
}
