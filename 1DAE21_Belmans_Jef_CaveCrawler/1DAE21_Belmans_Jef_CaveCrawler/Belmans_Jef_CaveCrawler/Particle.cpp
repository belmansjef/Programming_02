#include <cmath>
#include "pch.h"
#include "utils.h"
#include "Particle.h"
#include "Time.h"

bool Particle::IsAlive() const
{
	return m_IsAlive;
}

void Particle::Initialize(const Vector2f& velocity, float startSize, float endSize, float lifetime)
{
	m_Velocity = velocity;

	m_StartSize = m_CurrentSize = startSize;
	m_EndSize = endSize;
	m_StartLifetime = m_RemainingLifetime = lifetime;

	m_Graphic.width = m_Graphic.height = m_CurrentSize;
}

void Particle::Instantiate(const Point2f& position)
{

	m_Position = position;
	m_Graphic.left = m_Position.x - m_StartSize / 2.0f;
	m_Graphic.bottom = m_Position.y - m_StartSize / 2.0f;

	m_IsAlive = true;
}

void Particle::Reset()
{
	m_IsAlive = false;
	m_CurrentSize = m_StartSize;
	m_RemainingLifetime = m_StartLifetime;
}

void Particle::Update()
{
	m_RemainingLifetime -= Time::GetInstance()->m_DeltaTime;
	if (m_RemainingLifetime <= 0 || m_CurrentSize <= m_EndSize)
	{
		m_IsAlive = false;
	}

	m_CurrentSize = std::lerp(m_StartSize, m_EndSize, m_StartLifetime - m_RemainingLifetime);
	m_Graphic.width = m_CurrentSize;
	m_Graphic.height = m_CurrentSize;
	m_Graphic.left += m_Velocity.x * Time::GetInstance()->m_DeltaTime;
	m_Graphic.bottom += m_Velocity.y * Time::GetInstance()->m_DeltaTime;
}

void Particle::Draw() const
{
	glPushMatrix();
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
		utils::FillRect(m_Graphic);
	glPopMatrix();
}
