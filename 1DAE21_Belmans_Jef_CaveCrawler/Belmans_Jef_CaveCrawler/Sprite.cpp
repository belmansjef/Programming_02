#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(const SpriteType& type)
	: m_Type { type }
{
	UpdateSprite();
}

Sprite::~Sprite()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Sprite::Draw() const
{
	m_pTexture->Draw();
}

void Sprite::Update(float elapsedSec)
{
	m_FrameAccuSec += elapsedSec;
	if (m_FrameAccuSec >= 1.0f / m_NrFramesPerSec)
	{
		m_CurrentFrame++;
		m_FrameAccuSec = 0.0f;

		m_TextureClip = Rectf
		{
			// TODO: Add texture clip
		};
	}
}

void Sprite::SetType(const SpriteType& type)
{
	m_Type = type;
	UpdateSprite();
}

void Sprite::UpdateSprite()
{
	switch (m_Type)
	{
	case Sprite::SpriteType::player:
		m_pTexture = new Texture{ "Resources/Images/..." };
		break;
	case Sprite::SpriteType::crab:
		m_pTexture = new Texture{ "Resources/Images/..." };
		break;
	case Sprite::SpriteType::bat:
		m_pTexture = new Texture{ "Resources/Images/..." };
		break;
	case Sprite::SpriteType::hazard:
		m_pTexture = new Texture{ "Resources/Images/..." };
		break;
	default:
		break;
	}
}
