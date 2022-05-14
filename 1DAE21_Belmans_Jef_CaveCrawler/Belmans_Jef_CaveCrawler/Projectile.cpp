#include "Projectile.h"
#include "pch.h"
#include "utils.h"
#include "Texture.h"
#include "SoundManager.h"

Projectile::Projectile()
	: m_IsInstanciated { false }
	, m_AngleRad{ 0.0f }
	, m_AngleDeg{ 0.0f }
	, m_pTexture { new Texture("Resources/Images/Sprite_ProjectileSmall.png")}
{
}

Projectile::Projectile(const Vector2f& velocity, const Rectf& boxCollider)
	: m_IsInstanciated{ false }
	, m_Velocity { velocity }
	, m_BoxCollider { boxCollider }
	, m_pTexture{ new Texture("Resources/Images/Sprite_ProjectileSmall.png") }
{
	m_AngleRad = atan2f(m_Velocity.y, m_Velocity.x) * float(180.0f / M_PI);
	m_AngleDeg = m_AngleRad * float(180.0f / M_PI);
	
}

Projectile::~Projectile()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Projectile::Instanciate(const Vector2f& velocity, const Point2f& bottomLeft)
{
	m_Velocity = velocity;
	m_BoxCollider = Rectf
	(
		bottomLeft.x,
		bottomLeft.y,
		m_pTexture->GetWidth(),
		m_pTexture->GetHeight()
	);
	m_AngleRad = atan2f(m_Velocity.y, m_Velocity.x);
	m_AngleDeg = m_AngleRad * float(180.0f / M_PI);
	m_IsInstanciated = true;
}

bool Projectile::IsInstanciated() const
{
	return m_IsInstanciated;
}

void Projectile::Update()
{
	m_BoxCollider.left += m_Velocity.x * Time::deltaTime;
	m_BoxCollider.bottom += m_Velocity.y * Time::deltaTime;
}

void Projectile::Draw() const
{
	glPushMatrix();
		glTranslatef(m_BoxCollider.left, m_BoxCollider.bottom, 0);
		glRotatef(m_AngleDeg, 0, 0, 1);
		m_pTexture->Draw();

	glPopMatrix();
}

void Projectile::Reset()
{
	m_IsInstanciated = false;
}

bool Projectile::HitCheck(const std::vector<Point2f>& verts)
{
	const Point2f startPos = Point2f{ m_BoxCollider.left, m_BoxCollider.bottom + m_BoxCollider.height / 2.0f };
	const Point2f endPos = Point2f{ startPos.x + (cosf(m_AngleRad) * 4.0f), startPos.y + (sinf(m_AngleRad) * 4.0f) };
	utils::HitInfo hitInfo;

	if (utils::Raycast(verts, startPos, endPos, hitInfo))
	{
		m_IsInstanciated = false;
		SoundManager::GetInstance()->PlaySound(SoundType::hitWall);
	}

	return !m_IsInstanciated;
}

bool Projectile::HitCheck(const Rectf& rect)
{
	if (utils::IsOverlapping(rect, m_BoxCollider))
	{
		m_IsInstanciated = false;
	}

	return !m_IsInstanciated;
}
