#include "DamageBlock.h"
#include "utils.h"

DamageBlock::DamageBlock(float left, float bottom)
	: m_Sprite{ Sprite(SpriteType::damageBlock) }
	, m_Shape{ Rectf (left, bottom, 8.0f, 8.0f) }
{
}

DamageBlock::~DamageBlock()
{
}

bool DamageBlock::IsOverlapping(const Rectf& rect)
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
