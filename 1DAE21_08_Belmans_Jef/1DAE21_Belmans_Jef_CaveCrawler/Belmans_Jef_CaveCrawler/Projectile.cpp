#include "Projectile.h"
#include "pch.h"
#include "utils.h"

Projectile::Projectile()
	: m_IsInstanciated { false }
	, m_Angle{ 0.0f }
{
}

Projectile::Projectile(const Vector2f& velocity, const Rectf& rectGraphic)
	: m_IsInstanciated{ false }
	, m_Velocity { velocity }
	, m_RectGraphic { rectGraphic }
{
	m_Angle = atan2f(m_Velocity.y, m_Velocity.x);
}

void Projectile::Instanciate(const Vector2f& velocity, const Point2f& bottomLeft)
{
	m_Velocity = velocity;
	m_RectGraphic = Rectf
	(
		bottomLeft.x,
		bottomLeft.y,
		6.0f,
		2.0f
	);

	m_IsInstanciated = true;
}

bool Projectile::IsInstanciated() const
{
	return m_IsInstanciated;
}

void Projectile::Update()
{
	m_RectGraphic.left += m_Velocity.x * Time::deltaTime;
	m_RectGraphic.bottom += m_Velocity.y * Time::deltaTime;
}

void Projectile::Draw() const
{
	glPushMatrix();
		glRotatef(m_Angle, 0, 0, 1);
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
		utils::FillRect(m_RectGraphic);
	glPopMatrix();
}

void Projectile::Reset()
{
	m_IsInstanciated = false;
}

bool Projectile::HitCheck(const std::vector<Point2f>& verts)
{
	const Point2f startPos = Point2f{ m_RectGraphic.left, m_RectGraphic.bottom + m_RectGraphic.height / 2.0f };
	const Point2f endPos = Point2f{ m_RectGraphic.left + m_RectGraphic.width, startPos.y };
	utils::HitInfo hitInfo;

	if (utils::Raycast(verts, startPos, endPos, hitInfo))
	{
		m_IsInstanciated = false;
	}

	return !m_IsInstanciated;
}

bool Projectile::HitCheck(const Rectf& rect)
{
	if (utils::IsOverlapping(rect, m_RectGraphic))
	{
		m_IsInstanciated = false;
	}

	return !m_IsInstanciated;
}
