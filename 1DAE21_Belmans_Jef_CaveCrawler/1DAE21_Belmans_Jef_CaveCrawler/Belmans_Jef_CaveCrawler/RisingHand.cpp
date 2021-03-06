#include "RisingHand.h"
#include "pch.h"
#include "utils.h"
#include "ParticleSystem.h"
#include "SoundManager.h"
#include "Enums.h"

RisingHand::RisingHand(const Point2f& bottomLeft, int maxHealth)
	: m_Sprite { Sprite(SpriteType::risingHand)}
	, m_Health { Health(maxHealth, &m_Sprite, 0.1f) }
	, m_MaxHealth { maxHealth }
	, m_pDeathPS { new ParticleSystem(15) }
{
	m_BoxCollider = Rectf
	{
		bottomLeft.x,
		bottomLeft.y,
		8.0f,
		14.0f
	};

	m_pDeathPS->Initialize(Point2f(-20.0f, -20.0f), Point2f{ 20.0f, 20.0f }, Point2f(2.0f, 3.0f), Point2f(0.1f, 0.1f), Point2f(1.5f, 2.5f));
}

RisingHand::~RisingHand()
{
	delete m_pDeathPS;
	m_pDeathPS = nullptr;
}

Rectf RisingHand::GetBoxCollider() const
{
	return m_BoxCollider;
}

bool RisingHand::IsDead() const
{
	return m_Health.GetIsDead();
}

bool RisingHand::IsOverlapping(const Rectf& actorShape) const
{
	return utils::IsOverlapping(m_BoxCollider, actorShape);
}

void RisingHand::TakeDamage(int damage)
{
	m_Health.TakeDamage(damage);
	if (m_Health.GetIsDead() && !m_pDeathPS->IsPlaying())
	{
		m_pDeathPS->PlayAtPos(Point2f(m_BoxCollider.left + m_BoxCollider.width / 2.0f, m_BoxCollider.bottom + m_BoxCollider.height / 2.0f));
	}
}

void RisingHand::Update(const Rectf& actorShape)
{
	if (!m_Health.GetIsDead())
	{
		m_BoxCollider.height = 14.0f;
		if (utils::IsOverlapping(m_BoxCollider, actorShape))
		{
			m_Sprite.SetAnimation("grabbing");
		}
		else if (utils::GetDistance(Point2f(actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.height / 2.0f), Point2f(m_BoxCollider.left + m_Sprite.GetFrameWidth() / 2.0f, m_BoxCollider.bottom + m_Sprite.GetFrameHeight() / 2.0f)) <= m_TriggerDistance)
		{
			m_Sprite.SetAnimation("extended");
			if (!m_HasExtended)	SoundManager::GetInstance()->PlaySound(SoundType::handRise);

			m_HasExtended = true;
		}
		else
		{
			m_Sprite.SetAnimation("idle");
			m_BoxCollider.height = 0.0f;
			m_HasExtended = false;
		}
		m_Sprite.Update();
	}
	
	m_pDeathPS->Update();
}

void RisingHand::Draw() const
{
	if (!m_Health.GetIsDead())
	{
		glPushMatrix();
		glTranslatef(m_BoxCollider.left - m_HorDrawOffset, m_BoxCollider.bottom, 0);
		m_Sprite.Draw();
		glPopMatrix();
	}
	

	m_pDeathPS->Draw();
}

void RisingHand::Reset()
{
	m_Health.Heal(m_MaxHealth);
	m_Sprite.SetAnimation("idle");
}

