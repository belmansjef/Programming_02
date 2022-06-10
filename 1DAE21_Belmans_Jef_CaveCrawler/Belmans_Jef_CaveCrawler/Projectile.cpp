#include "Projectile.h"
#include "pch.h"
#include "utils.h"
#include "Texture.h"
#include "SoundManager.h"
#include "Enums.h"
#include "ParticleSystem.h"

Projectile::Projectile(ProjectileType type)
	: m_IsInstanciated { false }
	, m_AngleRad{ 0.0f }
	, m_AngleDeg{ 0.0f }
	, m_pTexture { type == ProjectileType::small ? new Texture("Resources/Images/Sprite_ProjectileSmall.png")
												 : new Texture("Resources/Images/Sprite_ProjectileLarge.png") }
	, m_pHitPS { new ParticleSystem(10) }
{
	m_pHitPS->Initialize(Point2f(-15.0f, -15.0f), Point2f(15.0f, 15.0f), Point2f(2.0f, 3.0f), Point2f(0.1f, 0.1f), Point2f(0.3f, 0.45f));
}

Projectile::Projectile(const Vector2f& velocity, const Rectf& boxCollider)
	: m_IsInstanciated{ false }
	, m_Velocity { velocity }
	, m_BoxCollider { boxCollider }
	, m_pTexture{ new Texture("Resources/Images/Sprite_ProjectileSmall.png") }
	, m_pHitPS{ new ParticleSystem(10) }
{
	m_AngleRad = atan2f(m_Velocity.y, m_Velocity.x) * float(180.0f / M_PI);
	m_AngleDeg = m_AngleRad * float(180.0f / M_PI);
	m_pHitPS->Initialize(Point2f(-15.0f, -15.0f), Point2f(15.0f, 15.0f), Point2f(2.0f, 3.0f), Point2f(0.1f, 0.1f), Point2f(0.3f, 0.45f));
}

Projectile::~Projectile()
{
	delete m_pTexture;
	delete m_pHitPS;

	m_pTexture = nullptr;
	m_pHitPS = nullptr;
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
	m_AngleDeg = float(int(m_AngleRad * float(180.0f / M_PI) + 360) % 360);
	m_IsInstanciated = true;

	m_Ray.start = Point2f(m_BoxCollider.left, m_BoxCollider.bottom);
	m_Ray.end = Point2f(m_Ray.start.x + (cosf(m_AngleRad) * 4.0f), m_Ray.start.y + (sinf(m_AngleRad) * 4.0f));
}

bool Projectile::IsInstanciated() const
{
	return m_IsInstanciated;
}

bool Projectile::IsEmittingParticles() const
{
	return m_pHitPS->IsPlaying();
}

void Projectile::Update()
{
	if (m_IsInstanciated)
	{
		const float deltaTime{ Time::GetInstance()->m_DeltaTime };
		m_BoxCollider.left += m_Velocity.x * deltaTime;
		m_BoxCollider.bottom += m_Velocity.y * deltaTime;

		m_Ray.start.x += m_Velocity.x * deltaTime;
		m_Ray.start.y += m_Velocity.y * deltaTime;

		m_Ray.end.x += m_Velocity.x * deltaTime;
		m_Ray.end.y += m_Velocity.y * deltaTime;
	}

	if (m_pHitPS->IsPlaying())
	{
		m_pHitPS->Update();
	}
}

void Projectile::Draw() const
{
	if (m_IsInstanciated)
	{
		glPushMatrix();
		glTranslatef(m_BoxCollider.left, m_BoxCollider.bottom, 0);
		glRotatef(m_AngleDeg, 0, 0, 1);
		glTranslatef(-m_BoxCollider.width / 2.0f, -m_BoxCollider.height / 2.0f, 0);
		m_pTexture->Draw();
		glPopMatrix();
	}
	
	if (m_pHitPS->IsPlaying())
	{
		m_pHitPS->Draw();
	}
}

void Projectile::Reset()
{
	m_IsInstanciated = false;
	m_pHitPS->Stop();
}

bool Projectile::HitCheck(const std::vector<Point2f>& verts)
{
	utils::HitInfo hitInfo;

	if (utils::Raycast(verts, m_Ray, hitInfo))
	{
		m_IsInstanciated = false;
		m_pHitPS->PlayAtPos(hitInfo.intersectPoint);
		SoundManager::GetInstance()->PlaySound(SoundType::hitWall);
	}

	return !m_IsInstanciated;
}

bool Projectile::HitCheck(const Rectf& rect)
{
	const std::vector<Point2f> verts
	{
		Point2f(rect.left, rect.bottom),
		Point2f(rect.left + rect.width, rect.bottom),
		Point2f(rect.left + rect.width, rect.bottom + rect.height),
		Point2f(rect.left, rect.bottom + rect.height)
	};

	utils::HitInfo hitInfo;
	if (utils::Raycast(verts, m_Ray, hitInfo))
	{
		m_IsInstanciated = false;
		m_pHitPS->PlayAtPos(hitInfo.intersectPoint);
	}

	return !m_IsInstanciated;
}
