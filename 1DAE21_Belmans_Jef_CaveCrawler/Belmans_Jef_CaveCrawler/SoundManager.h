#pragma once
#include <vector>
#include <unordered_map>
#include "pch.h"
#include "SoundEffect.h"
#include "SoundStream.h"

enum class SoundType;
class SoundManager final
{
public:
	static SoundManager* GetInstance();
	~SoundManager();

	void PlayMainSoundtrack();
	void StopMainSoundtrack();
	void PlayBossSoundtrack();
	void StopBossSoundtrack();
	void PlaySound(const SoundType& sound) const;
	void AdjustVolume(float value);
	float GetVolume() const;

	void Initialize(const std::string& filePath);

private:
	SoundManager() = default;
	std::unordered_map<SoundType, SoundEffect*> m_pSoundEffects;
	SoundStream m_MainSoundtrack{ "Resources/Sounds/Soundtrack.ogg" };
	SoundStream m_BossSoundtrack{ "Resources/Sounds/BossSoundtrack.wav" };

	const float m_MaxVolume{ 80.0f };
	float m_CurrentVolume{ 20.0f };

	void ApplyVolume();
};