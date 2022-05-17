#include "DamageBlock.h"
#include "utils.h"
#include "pch.h"
#include "Enums.h"

DamageBlock::DamageBlock(float left, float bottom)
	: m_Sprite{ Sprite(SpriteType::damageBlock) }
	, m_Shape{ Rectf (left, bottom, 8.0f, 8.0f) }
{
}

bool DamageBlock::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(m_Shape, rect);
}

void DamageBlock::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		m_Sprite.Draw();
	glPopMatrix();
}

void DamageBlock::Update()
{
	m_Sprite.Update();
}
