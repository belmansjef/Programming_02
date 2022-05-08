#include <iostream>
#include "SoundManager.h"


SoundManager* SoundManager::m_pSingleton{ nullptr };

SoundManager* SoundManager::GetInstance()
{
	if (m_pSingleton == nullptr)
	{
		m_pSingleton = new SoundManager();
	}

	return m_pSingleton;
}

SoundManager::~SoundManager()
{
	delete m_pSingleton;
	m_pSingleton = nullptr;
}

void SoundManager::PlaySound(const SoundType& sound) const
{
	std::map<SoundType, SoundEffect*>::const_iterator cit = m_pSoundEffects.find(sound);
	if (cit != m_pSoundEffects.end())
	{
		cit->second->Play(0);
	}
	else std::cout << "Sound " << int(sound) << " not found!" << std::endl;
}

SoundManager::SoundManager()
{
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::selectUI, new SoundEffect("Resources/Sounds/SelectUI.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::enterUI, new SoundEffect("Resources/Sounds/EnterUI.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::explosion, new SoundEffect("Resources/Sounds/Explosion.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::coinPickup, new SoundEffect("Resources/Sounds/CoinPickup.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::healthPickup, new SoundEffect("Resources/Sounds/HealthPickup.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::handRise, new SoundEffect("Resources/Sounds/HandRise.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::hitHurt, new SoundEffect("Resources/Sounds/HitHurt.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::hitWall, new SoundEffect("Resources/Sounds/HitWall.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::jump, new SoundEffect("Resources/Sounds/Jump.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::shoot, new SoundEffect("Resources/Sounds/Shoot.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::spikeFall, new SoundEffect("Resources/Sounds/SpikeFall.wav")));
	m_pSoundEffects.insert(std::pair<SoundType, SoundEffect*>(SoundType::levelFinish, new SoundEffect("Resources/Sounds/LevelFinish.wav")));
	SetMasterVolume(25);
}

void SoundManager::SetMasterVolume(int value)
{
	for (auto const& [key, val] : m_pSoundEffects)
	{
		val->SetVolume(value);
	}
}
