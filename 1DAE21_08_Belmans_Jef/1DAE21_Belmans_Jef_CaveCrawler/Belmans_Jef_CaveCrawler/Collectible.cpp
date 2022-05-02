#include "pch.h"
#include "Collectible.h"
#include "utils.h"
#include "Texture.h"

Collectible::Collectible(const Point2f& bottomLeft, Collectible::CollectibleType type)
	: m_Type{ type }
	, m_pTexture{ new Texture{ type == Collectible::CollectibleType::points ? "./Resources/Images/Collectible_Points.png" : "./Resources/Images/Collectible_Health.png"} }
	, m_IsPickedUp { false }
{
	m_Shape = Rectf{bottomLeft.x, bottomLeft.y, m_pTexture->GetWidth(), m_pTexture->GetHeight()};
}

Collectible::~Collectible()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

Collectible::CollectibleType Collectible::GetType() const
{
	return m_Type;
}

bool Collectible::GetIsPickedUp() const
{
	return m_IsPickedUp;
}

void Collectible::SetIsPickedUp(bool isPickedUp)
{
	m_IsPickedUp = isPickedUp;
}

void Collectible::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		m_pTexture->Draw();
	glPopMatrix();
}

bool Collectible::IsOverlapping(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_Shape);
}
