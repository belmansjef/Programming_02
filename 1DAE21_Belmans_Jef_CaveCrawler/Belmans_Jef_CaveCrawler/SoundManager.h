#pragma once
#include "SoundEffect.h"

class SoundManager final
{
public:
	static SoundManager* GetInstance();

	void PlayBlipSelect();
	void PlayCoinPickup();
	void PlayHealthPickup();
	void PlayExplosion();
	void PlayHandRise();
	void PlayHitHurt();
	void PlayHitWall();
	void PlayJump();
	void PlayShoot();
	void PlaySpikeFall();
	void SetMasterVolume(int value);

protected:
	SoundManager();
	static SoundManager* m_Singleton;

	int m_MasterVolume{ 25 };

	SoundEffect m_BlipSelectSE{ "Resources/Sounds/BlipSelect.wav" };
	SoundEffect m_CoinPickupSE{ "Resources/Sounds/CoinPickup.wav" };
	SoundEffect m_HealthPickupSE{ "Resources/Sounds/HealthPickup.wav" };
	SoundEffect m_ExplosionSE{ "Resources/Sounds/Explosion.wav" };
	SoundEffect m_HandRiseSE{ "Resources/Sounds/HandRise.wav" };
	SoundEffect m_HitHurtSE{ "Resources/Sounds/HitHurt.wav" };
	SoundEffect m_HitWallSE{ "Resources/Sounds/HitWall.wav" };
	SoundEffect m_JumpSE{ "Resources/Sounds/Jump.wav" };
	SoundEffect m_ShootSE{ "Resources/Sounds/Shoot.wav" };
	SoundEffect m_SpikeFallSE{ "Resources/Sounds/SpikeFall.wav" };
};