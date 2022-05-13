#include "pch.h"
#include "CannonEnemy.h"

CannonEnemy::CannonEnemy(const Point2f& bottomLeft, float orientation)
	: m_SpriteBase { SpriteType::cannonEnemyBase }
	, m_SpriteBarrel { SpriteType::cannonEnemyBarrel }
	, m_Health { 3, &m_SpriteBase }
	, m_BaseOrientation { orientation }
	, m_BarrelAngle { 0.0f }
{
	m_BoxCollider = Rectf
	(
		bottomLeft.x,
		bottomLeft.y,
		m_SpriteBase.GetFrameWidth(),
		m_SpriteBase.GetFrameHeight()
	);
}

void CannonEnemy::Update(const Rectf& actorShape)
{
	const Point2f baseVec (m_BoxCollider.left + m_SpriteBase.GetFrameWidth() / 2.0f
		, m_BoxCollider.bottom + m_SpriteBase.GetFrameHeight() / 2.0f);
	const Point2f freeVec(actorShape.left + actorShape.width / 2.0f - baseVec.x, actorShape.bottom + actorShape.height / 2.0f - baseVec.y);

	m_BarrelAngle = atan2f(freeVec.y, freeVec.x) * float(180.0f / M_PI) - 90.0f; // need to offset by -90 degrees because default orientation is up
}

void CannonEnemy::Draw() const
{
	// Draw barrel
	glPushMatrix();
		glTranslatef
		(
			m_BoxCollider.left + m_SpriteBase.GetFrameWidth() / 2.0f
			, m_BoxCollider.bottom + m_SpriteBase.GetFrameHeight() / 2.0f
			, 0
		);
		glRotatef(m_BarrelAngle, 0, 0, 1);
		glTranslatef(- m_SpriteBarrel.GetFrameWidth() / 2.0f, 6.0f, 0);
		m_SpriteBarrel.Draw();
	glPopMatrix();

	// Draw base
	glPushMatrix();
		glTranslatef(m_BoxCollider.left, m_BoxCollider.bottom, 0);
		glRotatef(m_BaseOrientation, 0, 0, 1);
		if (m_BaseOrientation == 180.0f)
		{
			glTranslatef(-m_SpriteBase.GetFrameWidth(), -m_SpriteBase.GetFrameHeight(), 0);
		}
		
		m_SpriteBase.Draw();
	glPopMatrix();
}
