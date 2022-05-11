#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "SoundManager.h"


SoundManager* SoundManager::m_pInstance{ nullptr };

SoundManager* SoundManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SoundManager();
	}

	return m_pInstance;
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

void SoundManager::Initialize()
{
	std::ifstream soundfile{ "Resources/Initializers/Sounds.txt" };

	if (soundfile.good())
	{
		while (soundfile.peek() != EOF)
		{
			std::string line;
			std::getline(soundfile, line, '>');
			int Type{ std::stoi(GetAttributeValue("Type", line)) };
			std::string Path{ GetAttributeValue("Path", line) };

			if (Path != "")
			{
				
				m_pSoundEffects.insert(std::make_pair(SoundType(Type), new SoundEffect(Path)));
			}
		}
	}
	ApplyVolume();
}

void SoundManager::Destroy()
{
	for (auto& [key, val] : m_pSoundEffects)
	{
		delete val;
		val = nullptr;
	}

	delete m_pInstance;
	m_pInstance = nullptr;
}

void SoundManager::ApplyVolume()
{
	for (auto& [key, val] : m_pSoundEffects)
	{
		val->SetVolume(int(m_CurrentVolume));
	}
}

std::string SoundManager::GetAttributeValue(const std::string& attrName, const std::string& element)
{
	std::string attribute;
	std::string attrSearch{ attrName + "=" };

	size_t attrPos = element.find(attrSearch);
	if (attrPos == std::string::npos)
	{
		std::cerr << R"(Attribute ")" << attrName << R"(" not found!)";
		return "";
	}
	size_t startPos{ element.find(R"(")", attrPos) };
	size_t endPos{ element.find(R"(")", startPos + 1) };

	attribute = element.substr(startPos + 1, endPos - startPos - 1);
	return attribute;
}
