#include "Platform.h"
#include "Texture.h"
#include "utils.h"

Platform::Platform(const Point2f bottomLeft)
	: m_pTexture{ new Texture("Resources/Images/platform.png") }
{
	m_Shape = Rectf(bottomLeft.x, bottomLeft.y, m_pTexture->GetWidth(), m_pTexture->GetHeight());
}

Platform::~Platform()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Platform::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		m_pTexture->Draw();
	glPopMatrix();
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	if (actorVelocity.y > 0.0f) return;

	const int castDepth{ 2 };
	const Rectf collisionCast
	{
		actorShape.left,
		actorShape.bottom - castDepth,
		actorShape.width,
		5.0f
	};

	if (utils::IsOverlapping(collisionCast, m_Shape) && actorShape.bottom - m_Shape.bottom > m_Shape.height - 5.0f)
	{
		actorShape.bottom = m_Shape.bottom + m_Shape.height;
	}
}

bool Platform::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	if (actorVelocity.y > 0.0f) return false;

	const int castDepth{ 2 };
	const Rectf collisionCast
	{
		actorShape.left,
		actorShape.bottom - castDepth,
		actorShape.width,
		5.0f
	};

	const Rectf collider
	{
		m_Shape.left,
		m_Shape.bottom + m_Shape.height - castDepth,
		m_Shape.width,
		castDepth
	};

	return utils::IsOverlapping(collisionCast, collider);
}
