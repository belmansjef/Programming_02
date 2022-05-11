#pragma once
#include <vector>
#include <unordered_map>
#include "SoundEffect.h"
#include "Enums.h"

class SoundManager final
{
public:
	static SoundManager* GetInstance();

	void PlaySound(const SoundType& sound) const;
	void AdjustVolume(float value);
	float GetVolume() const;
	void Initialize();
	void Destroy();

private:
	static SoundManager* m_pInstance;

	const float m_MaxVolume{ 80.0f };
	float m_CurrentVolume{ 50.0f };

	std::unordered_map<SoundType, SoundEffect*> m_pSoundEffects;

	void ApplyVolume();
	std::string GetAttributeValue(const std::string& attrName, const std::string& element);
};