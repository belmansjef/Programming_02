#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "FileReader.h"
#include "SoundManager.h"
#include "Enums.h"

SoundManager* SoundManager::GetInstance()
{
	static SoundManager* s = new SoundManager();
	return s;
}

void SoundManager::PlaySound(const SoundType& sound) const
{
	std::unordered_map<SoundType, SoundEffect*>::const_iterator cit = m_pSoundEffects.find(sound);
	if (cit != m_pSoundEffects.end())
	{
		cit->second->Play(0);
	}
	else std::cout << "Tried to play a sound that doesn't exist!" << std::endl;
}

void SoundManager::AdjustVolume(float value)
{
	m_CurrentVolume = std::clamp(m_CurrentVolume + value, 0.0f, m_MaxVolume);
	ApplyVolume();
}

float SoundManager::GetVolume() const
{
	return m_CurrentVolume;
}

void SoundManager::Initialize(const std::string& filePath)
{
	std::ifstream file{ filePath };

	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string line;
			std::getline(file, line, '>');
			int Type{ std::stoi(FileReader::GetAttributeValue("Type", line)) };
			std::string Path{ FileReader::GetAttributeValue("Path", line) };

			if (Path != "")
			{
				m_pSoundEffects.insert(std::make_pair(SoundType(Type), new SoundEffect(Path)));
			}
		}
	}
	ApplyVolume();
}

SoundManager::~SoundManager()
{
	for (std::pair<SoundType, SoundEffect*> key_val : m_pSoundEffects)
	{
		delete key_val.second;
		key_val.second = nullptr;
	}
}

void SoundManager::PlayMainSoundtrack()
{
	m_MainSoundtrack.Play(true);
}

void SoundManager::StopMainSoundtrack()
{
	m_MainSoundtrack.Stop();
}

void SoundManager::PlayBossSoundtrack()
{
	m_BossSoundtrack.Play(true);
}

void SoundManager::StopBossSoundtrack()
{
	m_BossSoundtrack.Stop();
}

void SoundManager::ApplyVolume()
{
	for (std::pair<SoundType, SoundEffect*> key_val : m_pSoundEffects)
	{
		key_val.second->SetVolume(int(m_CurrentVolume));
	}

	m_MainSoundtrack.SetVolume(int(m_CurrentVolume));
	m_BossSoundtrack.SetVolume(int(m_CurrentVolume));
}
