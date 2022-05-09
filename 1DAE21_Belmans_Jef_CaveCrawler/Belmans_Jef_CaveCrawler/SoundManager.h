#pragma once
#include <vector>
#include <unordered_map>
#include "SoundEffect.h"

enum class SoundType
{
	selectUI = 0,
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

enum class SoundCategory
{
	master,
	music,
	effects
};

class SoundManager final
{
public:
	static SoundManager* GetInstance();

	void PlaySound(const SoundType& sound) const;
	void AdjustVolume(const SoundCategory& soundCategory, float value);
	void Initialize();
	void Destroy();

protected:
	static SoundManager* m_pInstance;

	const float m_MaxVolume{ 80.0f };
	float m_MusicVolume{ 50.0f };
	float m_EffectsVolume{ 50.0f };

	std::unordered_map<SoundType, SoundEffect*> m_pSoundEffects;

	void ApplyVolume();
	std::string GetAttributeValue(const std::string& attrName, const std::string& element);
};