#pragma once
#include <string>
#include <unordered_map>

class Texture;
class TextureManager final
{
public:
	TextureManager() = default;
	~TextureManager();

	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;

	Texture* GetTexture(const std::string& fileName);

private:
	std::unordered_map<std::string, Texture*> m_pTextures;
};

