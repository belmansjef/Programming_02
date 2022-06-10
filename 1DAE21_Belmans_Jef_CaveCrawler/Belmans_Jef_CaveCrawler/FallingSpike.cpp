#include "FallingSpike.h"
#include "pch.h"
#include "utils.h"
#include "Texture.h"
#include "Camera.h"
#include "SoundManager.h"
#include "Enums.h"
#include "ParticleSystem.h"

FallingSpike::FallingSpike(const Point2f& bottomLeft)
	: m_pTexture { new Texture("Resources/Images/Sprite_FallingSpike.png")}
	, m_StartPos{ bottomLeft }
	, m_HasPlayedTriggerPS { false }
	, m_pTriggerPS { new ParticleSystem(10) }
	, m_pHitPS { new ParticleSystem(10) }
{
	m_BoxCollider = Rectf
	{
		bottomLeft.x,
		bottomLeft.y,
		m_pTexture->GetWidth(),
		m_pTexture->GetHeight()
	};

	m_pTriggerPS->Initialize(Point2f(-30.0f, -5.0f), Point2f(30.0f, 1.0f), Point2f(1.5f, 2.0f), Point2f(0.1f, 0.2f), Point2f(0.6f, 1.0f));
	m_pHitPS->Initialize(Point2f(-15.0f, -15.0f), Point2f(15.0f, 15.0f), Point2f(2.0f, 3.0f), Point2f(0.1f, 0.2f), Point2f(0.6f, 1.0f));
}

FallingSpike::~FallingSpike()
{
	delete m_pTexture;
	delete m_pHitPS;
	delete m_pTriggerPS;

	m_pTexture = nullptr;
	m_pHitPS = nullptr;
	m_pTriggerPS = nullptr;
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
	m_pHitPS->PlayAtPos(Point2f(m_BoxCollider.left + m_BoxCollider.width / 2.0f, m_BoxCollider.bottom + m_BoxCollider.height / 2.0f));
	Camera::DoScreenShake();
	SoundManager::GetInstance()->PlaySound(SoundType::explosion);
}

void FallingSpike::Update(const Rectf& actorShape)
{
	if (!m_IsDestroyed)
	{
		if (utils::GetDistance(Point2f(actorShape.left, actorShape.bottom), Point2f(m_BoxCollider.left, actorShape.bottom)) <= m_TriggerDistance.x + 16.0f
			&& actorShape.bottom >= m_BoxCollider.bottom - m_TriggerDistance.y
			&& actorShape.bottom <= m_BoxCollider.bottom && !m_HasPlayedTriggerPS)
		{
			m_pTriggerPS->PlayAtPos(Point2f(m_BoxCollider.left + m_BoxCollider.width / 2.0f, m_BoxCollider.bottom + m_BoxCollider.height));
			m_HasPlayedTriggerPS = true;
		}

		if (utils::GetDistance(Point2f(actorShape.left, actorShape.bottom), Point2f(m_BoxCollider.left, actorShape.bottom)) <= m_TriggerDistance.x
			&& actorShape.bottom >= m_BoxCollider.bottom - m_TriggerDistance.y
			&& actorShape.bottom <= m_BoxCollider.bottom && !m_IsFalling)
		{
			m_IsFalling = true;
			m_pTriggerPS->PlayAtPos(Point2f(m_BoxCollider.left + m_BoxCollider.width / 2.0f, m_BoxCollider.bottom + m_BoxCollider.height));

			SoundManager::GetInstance()->PlaySound(SoundType::spikeFall);
		}
		else if (m_IsFalling)
		{
			m_VelocityY += m_Gravity * Time::GetInstance()->m_DeltaTime;
			m_BoxCollider.bottom += m_VelocityY * Time::GetInstance()->m_DeltaTime;
		}
	}
	
	m_pHitPS->Update();
	m_pTriggerPS->Update();
}

void FallingSpike::Draw() const
{
	if (!m_IsDestroyed)
	{
		glPushMatrix();
		glTranslatef(m_BoxCollider.left, m_BoxCollider.bottom, 0);
		m_pTexture->Draw();
		glPopMatrix();
	}
	
	m_pHitPS->Draw();
	m_pTriggerPS->Draw();
}

void FallingSpike::Reset()
{
	m_BoxCollider.left = m_StartPos.x;
	m_BoxCollider.bottom = m_StartPos.y;
	m_VelocityY = 0.0f;
	m_IsDestroyed = false;
	m_IsFalling = false;
	m_HasPlayedTriggerPS = false;
}
