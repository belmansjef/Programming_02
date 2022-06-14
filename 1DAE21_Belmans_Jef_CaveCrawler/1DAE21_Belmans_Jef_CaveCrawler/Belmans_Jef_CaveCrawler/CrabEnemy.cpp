#include "pch.h"
#include "CrabEnemy.h"
#include "LevelBase.h"
#include "SoundManager.h"
#include "ParticleSystem.h"
#include "Enums.h"

CrabEnemy::CrabEnemy(float left, float bottom, float width, float height, int movementDirection, int maxHealth)
	: m_Health { Health(maxHealth, &m_Sprite, 0.1f) }
	, m_MaxHealth { maxHealth }
	, m_PhysicsBody { left, bottom, width, height }
	, m_MovementDirection { movementDirection }
	, m_Sprite { Sprite(SpriteType::crabEnemy) }
	, m_StartPos { left, bottom }
	, m_pDeathPS { new ParticleSystem(15) }
{
	m_pDeathPS->Initialize(Point2f(-20.0f, -20.0f), Point2f{ 20.0f, 20.0f }, Point2f(2.0f, 3.0f), Point2f(0.1f, 0.1f), Point2f(1.5f, 2.5f));
}

CrabEnemy::~CrabEnemy()
{
	delete m_pDeathPS;
	m_pDeathPS = nullptr;
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
	if (m_Health.GetIsDead() && !m_pDeathPS->IsPlaying())
	{
		m_pDeathPS->PlayAtPos(m_PhysicsBody.GetCenter());
	}
}

void CrabEnemy::Update(const LevelBase& level)
{
	if (!m_Health.GetIsDead())
	{
		m_PhysicsBody.Velocity().x = m_MovementDirection * m_MovementSpeed;
		m_PhysicsBody.Update(level);
		DoCollisionCheck(level.GetLevelVerts());

		m_Sprite.Update();
	}
	
	m_pDeathPS->Update();
}

void CrabEnemy::Draw() const
{
	if (!m_Health.GetIsDead())
	{
		glPushMatrix();
		glTranslatef(m_PhysicsBody.GetPosition().x, m_PhysicsBody.GetPosition().y, 0);
		m_Sprite.Draw();
		glPopMatrix();
	}
	

	m_pDeathPS->Draw();
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
