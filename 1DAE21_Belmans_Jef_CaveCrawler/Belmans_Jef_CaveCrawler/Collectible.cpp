#include "pch.h"
#include "Collectible.h"
#include "utils.h"
#include "Texture.h"

Collectible::Collectible(const Point2f& leftBottom, Collectible::Type type)
	: m_Type{ type }
	, m_pTexture{ new Texture{ type == Collectible::Type::points ? "./Resources/Images/Collectible_Points.png" : "./Resources/Images/Collectible_Health.png"} }
{
	m_Shape = Rectf{leftBottom.x, leftBottom.y, m_pTexture->GetWidth(), m_pTexture->GetHeight()};
}

Collectible::~Collectible()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Collectible::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		glScalef(2.0f, 2.0f, 1.0f);
		m_pTexture->Draw();
	glPopMatrix();
}

bool Collectible::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}
