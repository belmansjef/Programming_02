#include "TextureManager.h"
#include "Texture.h"

TextureManager::~TextureManager()
{
	for (auto& key_val : m_pTextures)
	{
		delete key_val.second;
		key_val.second = nullptr;
	}

	m_pTextures.clear();
}

Texture* TextureManager::GetTexture(const std::string& fileName)
{
	if (m_pTextures.at(fileName) == nullptr)
	{
		m_pTextures.insert(std::make_pair(fileName, new Texture(fileName)));
	}

	return m_pTextures.at(fileName);
}