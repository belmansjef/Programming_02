#include "RisingHand.h"
#include "utils.h"

RisingHand::RisingHand(const Point2f& bottomLeft, int maxHealth)
	: m_Sprite { Sprite(SpriteType::risingHand)}
	, m_Health { Health(maxHealth, 0.1f) }
{
	m_BoxCollider = Rectf
	{
		bottomLeft.x,
		bottomLeft.y,
		12.0f,
		18.0f
	};
}

Rectf RisingHand::GetBoxCollider() const
{
	return m_BoxCollider;
}

Health& RisingHand::GetHealth()
{
	return m_Health;
}

void RisingHand::Update(const Rectf& actorShape)
{ 
	m_BoxCollider.height = 18.0f;
	if (utils::IsOverlapping(m_BoxCollider, actorShape))
	{
		m_Sprite.SetAnimation("grabbing");
	}
	else if ( utils::GetDistance
	(	Point2f(actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.bottom / 2.0f)
		, Point2f(m_BoxCollider.left + m_Sprite.GetFrameWidth() / 2.0f, m_BoxCollider.bottom + m_Sprite.GetFrameHeight() / 2.0f)) <= m_TriggerDistance)
	{
		m_Sprite.SetAnimation("extended");
	}
	else
	{
		m_Sprite.SetAnimation("idle");
		m_BoxCollider.height = 0.0f;
	}

	m_Sprite.Update();
}

void RisingHand::Draw() const
{
	glPushMatrix();
		glTranslatef(m_BoxCollider.left, m_BoxCollider.bottom, 0);
		m_Sprite.Draw();
	glPopMatrix();
}

bool RisingHand::IsOverlapping(const Rectf& actorShape) const
{
	return utils::IsOverlapping(m_BoxCollider, actorShape);
}
