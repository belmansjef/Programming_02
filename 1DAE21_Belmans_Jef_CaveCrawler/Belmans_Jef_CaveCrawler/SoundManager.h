#pragma once
#include <map>
#include "SoundEffect.h"

enum class SoundType
{
	selectUI,
	enterUI,
	explosion,
	coinPickup,
	healthPickup,
	handRise,
	hitHurt,
	hitWall,
	jump,
	shoot,
	spikeFall,
	levelFinish
};

class SoundManager final
{
public:
	static SoundManager* GetInstance();
	~SoundManager();

	void PlaySound(const SoundType& sound) const;
	void SetMasterVolume(int value);

protected:
	SoundManager();
	static SoundManager* m_pSingleton;

	std::map<SoundType, SoundEffect*> m_pSoundEffects;
};