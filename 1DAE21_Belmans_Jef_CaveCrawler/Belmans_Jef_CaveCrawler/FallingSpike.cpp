#include "FallingSpike.h"
#include "pch.h"
#include "utils.h"
#include "Texture.h"
#include "Camera.h"
#include "SoundManager.h"

FallingSpike::FallingSpike(const Point2f& bottomLeft)
	: m_pTexture { new Texture("Resources/Images/Sprite_FallingSpike.png")}
	, m_StartPos{ bottomLeft }
{
	m_BoxCollider = Rectf
	{
		bottomLeft.x,
		bottomLeft.y,
		m_pTexture->GetWidth(),
		m_pTexture->GetHeight()
	};
}

FallingSpike::~FallingSpike()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

bool FallingSpike::IsDestroyed() const
{
	return m_IsDestroyed;
}

bool FallingSpike::IsFalling() const
{
	return m_IsFalling;
}

bool FallingSpike::IsOverlapping(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_BoxCollider);
}

bool FallingSpike::IsOverlapping(const std::vector<Point2f>& polygon)
{
	const Point2f startPos{ m_BoxCollider.left + m_BoxCollider.width / 2.0f, m_BoxCollider.bottom + m_BoxCollider.height };
	const Point2f endPos{ startPos.x, m_BoxCollider.bottom + m_BoxCollider.height / 2.0f };
	utils::HitInfo hitInfo;

	return utils::Raycast(polygon, startPos, endPos, hitInfo);
}

void FallingSpike::Destroy()
{
	m_IsDestroyed = true;
	Camera::DoScreenShake();
	SoundManager::GetInstance()->PlayExplosion();
}

void FallingSpike::Update(const Rectf& actorShape)
{
	if (utils::GetDistance(Point2f(actorShape.left, actorShape.bottom), Point2f(m_BoxCollider.left, actorShape.bottom)) <= m_TriggerDistance.x
		&& actorShape.bottom >= m_BoxCollider.bottom - m_TriggerDistance.y
		&& actorShape.bottom <= m_BoxCollider.bottom && !m_IsFalling)
	{
		m_IsFalling = true;
		SoundManager::GetInstance()->PlaySpikeFall();
	}
	else if(m_IsFalling)
	{
		m_VelocityY += m_Gravity * Time::deltaTime;
		m_BoxCollider.bottom += m_VelocityY * Time::deltaTime;
	}
}

void FallingSpike::Draw() const
{
	glPushMatrix();
		glTranslatef(m_BoxCollider.left, m_BoxCollider.bottom, 0);
		m_pTexture->Draw();
	glPopMatrix();
}

void FallingSpike::Reset()
{
	m_BoxCollider.left = m_StartPos.x;
	m_BoxCollider.bottom = m_StartPos.y;
	m_VelocityY = 0.0f;
	m_IsDestroyed = false;
	m_IsFalling = false;
}
