#include "Lava.h"
#include "utils.h"
#include "pch.h"
#include "Health.h"
#include "Avatar.h"

Lava::Lava(const Point2f& bottomLeft, float width, float height)
	: m_BoxCollider { Rectf(bottomLeft.x, bottomLeft.y, width, height)}
{
}

void Lava::Update(const Rectf& actorShape)
{
	if(PlayerOverlapCheck(actorShape))
	{
		Avatar::TakeDamage(10);
	}
}

void Lava::Draw() const
{
	utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	glPushMatrix();
		utils::FillRect(m_BoxCollider);
	glPopMatrix();
}

bool Lava::PlayerOverlapCheck(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_BoxCollider);
}
