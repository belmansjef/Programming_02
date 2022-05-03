#include "SoundManager.h"

SoundManager* SoundManager::m_Singleton{ nullptr };

SoundManager* SoundManager::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new SoundManager();
	}

	return m_Singleton;
}

SoundManager::SoundManager()
{
	SetMasterVolume(25);
}

void SoundManager::PlayBlipSelect()
{
	m_BlipSelectSE.Play(0);
}

void SoundManager::PlayCoinPickup()
{
	m_CoinPickupSE.Play(0);
}

void SoundManager::PlayHealthPickup()
{
	m_HealthPickupSE.Play(0);
}

void SoundManager::PlayExplosion()
{
	m_ExplosionSE.Play(0);
}

void SoundManager::PlayHandRise()
{
	m_HandRiseSE.Play(0);
}

void SoundManager::PlayHitHurt()
{
	m_HitHurtSE.Play(0);
}

void SoundManager::PlayHitWall()
{
	m_HitWallSE.Play(0);
}

void SoundManager::PlayJump()
{
	m_JumpSE.Play(0);
}

void SoundManager::PlayShoot()
{
	m_ShootSE.Play(0);
}

void SoundManager::PlaySpikeFall()
{
	m_SpikeFallSE.Play(0);
}

void SoundManager::SetMasterVolume(int value)
{
	m_MasterVolume = value;

	m_BlipSelectSE.SetVolume(m_MasterVolume);
	m_CoinPickupSE.SetVolume(m_MasterVolume);
	m_HealthPickupSE.SetVolume(m_MasterVolume);
	m_ExplosionSE.SetVolume(m_MasterVolume);
	m_HandRiseSE.SetVolume(m_MasterVolume);
	m_HitHurtSE.SetVolume(m_MasterVolume);
	m_HitWallSE.SetVolume(m_MasterVolume);
	m_JumpSE.SetVolume(m_MasterVolume);
	m_ShootSE.SetVolume(m_MasterVolume);
	m_SpikeFallSE.SetVolume(m_MasterVolume);
}
