#include "pch.h"
#include "Collectible.h"
#include "utils.h"
#include "ParticleSystem.h"
#include "Texture.h"
#include "Enums.h"

Collectible::Collectible(const Point2f& bottomLeft, CollectibleType type)
	: m_Type{ type }
	, m_pTexture{ new Texture{ type == CollectibleType::points ? "./Resources/Images/Collectible_Points.png" : "./Resources/Images/Collectible_Health.png"} }
	, m_IsPickedUp { false }
	, m_pPickUpPS { new ParticleSystem(8) }
{
	m_Shape = Rectf{bottomLeft.x, bottomLeft.y, m_pTexture->GetWidth(), m_pTexture->GetHeight()};
	m_pPickUpPS->Initialize(Point2f(-15.0f, -15.0f), Point2f(15.0f, 15.0f), Point2f(2.0f, 3.5f), Point2f(0.1f, 0.15f), Point2f(0.8f, 1.2f));
}

Collectible::~Collectible()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

CollectibleType Collectible::GetType() const
{
	return m_Type;
}

bool Collectible::GetIsPickedUp() const
{
	return m_IsPickedUp;
}

void Collectible::SetIsPickedUp(bool value)
{
	m_IsPickedUp = value;
}

void Collectible::PickUp()
{
	m_IsPickedUp = true;
	m_pPickUpPS->PlayAtPos(Point2f(m_Shape.left + m_Shape.width / 2.0f, m_Shape.bottom + m_Shape.height / 2.0f));
}

void Collectible::Update()
{
	m_pPickUpPS->Update();
}

void Collectible::Draw() const
{
	if (!m_IsPickedUp)
	{
		glPushMatrix();
			glTranslatef(m_Shape.left, m_Shape.bottom, 0);
			m_pTexture->Draw();
		glPopMatrix();
	}

	m_pPickUpPS->Draw();
}

bool Collectible::IsOverlapping(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_Shape);
}
