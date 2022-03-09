#include "Sprite.h"

Animation::Animation()
	: Animation("anim", 0, 0, 0, 0, 0, 0)
{
};

Animation::Animation(std::string animName, int nrFrames, int nrFramesPerSec, int nrRows, int nrCols, int rowOffset, int colOffset)
	: m_AnimName { animName }
	, m_NrFrames { nrFrames }
	, m_NrFramesPerSec{ nrFramesPerSec }
	, m_NrRows { nrRows }
	, m_NrCols { nrCols }
	, m_RowOffset { rowOffset }
	, m_ColOffset { colOffset }
{
}

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
	m_pTexture->Draw(Point2f(), m_TextureClip);
}

void Sprite::Update(float elapsedSec)
{
	m_FrameAccuSec += elapsedSec;
	if (m_FrameAccuSec >= 1.0f / m_pCurrentAnimation->m_NrFramesPerSec)
	{
		m_CurrentFrame = (m_CurrentFrame + 1) % m_pCurrentAnimation->m_NrFrames;
		m_FrameAccuSec = 0.0f;

		int widthIndex{ m_CurrentFrame % m_pCurrentAnimation->m_NrCols };
		int heightIndex{ m_CurrentFrame / m_pCurrentAnimation->m_NrCols + 1 };
		
		m_TextureClip.left = widthIndex * m_FrameWidth + (m_pCurrentAnimation->m_ColOffset * m_FrameWidth);
		m_TextureClip.bottom = heightIndex * m_FrameHeight + (m_pCurrentAnimation->m_RowOffset * m_FrameHeight);
	}
}

void Sprite::SetType(const SpriteType& type)
{
	m_Type = type;
	UpdateSprite();
}

void Sprite::SetAnimation(const std::string animName)
{
	if (animName == m_pCurrentAnimation->m_AnimName) return;

	for (Animation* ptr : m_Animations)
	{
		if (ptr->m_AnimName == animName)
		{
			m_CurrentFrame = 0;
			m_pCurrentAnimation = ptr;
		}
	}
}

void Sprite::UpdateSprite()
{
	m_Animations.clear();

	switch (m_Type)
	{
	case Sprite::SpriteType::player:
		m_pTexture = new Texture{ "Resources/Images/Sprite_Player.png" };
		m_SheetWidth = m_pTexture->GetWidth();
		m_SheetHeight = m_pTexture->GetHeight();
		m_FrameWidth = 24.0f;
		m_FrameHeight = 16.0f;

		m_CurrentFrame = 0;
		m_FrameAccuSec = 0;

		m_TextureClip = Rectf
		{
			0.0f,
			0.0f,
			m_FrameWidth,
			m_FrameHeight
		};

		m_Animations.push_back(new Animation("idle", 4, 5, 1, 4, 0, 0)); // Idle animation
		m_Animations.push_back(new Animation("run", 4, 10, 1, 4, 1, 0)); // Run animation
		m_Animations.push_back(new Animation("jump_up", 1, 10, 1, 1, 0, 4)); // Jump up animation
		m_Animations.push_back(new Animation("jump_down", 1, 10, 1, 1, 1, 4)); // Jump down animation
		m_pCurrentAnimation = m_Animations[0]; // Set current animation to idle
		break;
	default:
		break;
	}
}
