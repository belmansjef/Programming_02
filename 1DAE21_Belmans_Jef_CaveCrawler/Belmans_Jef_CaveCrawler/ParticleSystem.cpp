#include "ParticleSystem.h"
#include "Particle.h"
#include "pch.h"
#include "utils.h"

ParticleSystem::ParticleSystem(int numParticles)
	: m_IsPlaying { false }
{
	for (size_t i = 0; i < numParticles; i++)
	{
		m_pParticles.push_back(new Particle());
	}
}

ParticleSystem::~ParticleSystem()
{
	for (Particle* pParticle : m_pParticles) 
	{
		delete pParticle;
		pParticle = nullptr;
	}
}

bool ParticleSystem::IsPlaying() const
{
	return m_IsPlaying;
}

void ParticleSystem::PlayAtPos(const Point2f& pos)
{
	if (m_IsPlaying) return;

	for (Particle* pParticle : m_pParticles)
	{
		pParticle->Instantiate(pos);
	}

	m_IsPlaying = true;
}

void ParticleSystem::Stop()
{
	for (Particle* pParticle : m_pParticles)
	{
		pParticle->Reset();
	}
}

void ParticleSystem::Initialize(const Point2f& minVelocity, const Point2f& maxVelocity, const Point2f& startSizeRange, const Point2f& endSizeRange, const Point2f& lifetimeRange)
{
	for (Particle* pParticle : m_pParticles)
	{
		const Vector2f velocity
		{
			std::floorf(utils::GetRandomNumber(minVelocity.x, maxVelocity.x)),
			std::floorf(utils::GetRandomNumber(minVelocity.y, maxVelocity.y))
		};
		
		const float startSize{ utils::GetRandomNumber(startSizeRange.x, startSizeRange.y) };
		const float endSize{ utils::GetRandomNumber(endSizeRange.x, endSizeRange.y) };
		const float lifetime{ utils::GetRandomNumber(lifetimeRange.x, lifetimeRange.y)};

		pParticle->Initialize(velocity, startSize, endSize, lifetime);
	}
}

void ParticleSystem::Update()
{
	if (!m_IsPlaying) { return; }
	m_IsPlaying = false;

	for (Particle* pParticle : m_pParticles)
	{
		if (pParticle->IsAlive())
		{
			pParticle->Update();
			m_IsPlaying = true;
		}
	}

	if (!m_IsPlaying)
	{
		Stop();
	}
}

void ParticleSystem::Draw() const
{
	for (Particle* pParticle : m_pParticles)
	{
		if (pParticle->IsAlive())
		{
			pParticle->Draw();
		}
	}
}
