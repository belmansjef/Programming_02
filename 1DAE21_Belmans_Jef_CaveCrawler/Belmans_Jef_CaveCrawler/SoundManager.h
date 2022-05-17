#pragma once
#include <vector>
#include <unordered_map>
#include "SoundEffect.h"
#include "Enums.h"

class SoundManager final
{
public:
	static SoundManager* GetInstance();
	~SoundManager();

	void PlaySound(const SoundType& sound) const;
	void AdjustVolume(float value);
	float GetVolume() const;

	void Initialize(const std::string& filePath);

private:
	SoundManager() = default;
	std::unordered_map<SoundType, SoundEffect*> m_pSoundEffects;

	const float m_MaxVolume{ 80.0f };
	float m_CurrentVolume{ 50.0f };

	void ApplyVolume();
};