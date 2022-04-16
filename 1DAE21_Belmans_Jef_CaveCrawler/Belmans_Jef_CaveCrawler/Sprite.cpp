#include "Sprite.h"

Animation::Animation()
	: Animation("anim", 0, 0, 0, 0, 0, 0)
{
};

Animation::Animation(std::string animName, int nrFrames, int nrFramesPerSec, int nrRows, int nrCols, int rowOffset, int colOffset, bool holdLastFrame)
	: m_AnimName { animName }
	, m_NrFrames { nrFrames }
	, m_NrFramesPerSec{ nrFramesPerSec }
	, m_NrRows { nrRows }
	, m_NrCols { nrCols }
	, m_RowOffset { rowOffset }
	, m_ColOffset { colOffset }
	, m_HoldFirstFrame { holdLastFrame }
	, m_HoldTime{ 1.0f }
{
}

Sprite::Sprite(const SpriteType& type)
	: m_Type { type }
{
	SetSprite();
}

Sprite::~Sprite()
{
	delete m_pTexture;
	m_pTexture = nullptr;

	for (Animation* anim : m_pAnimations)
	{
		delete anim;
		anim = nullptr;
	}
}

float Sprite::GetFrameWidth() const
{
	return m_FrameWidth;
}

float Sprite::GetFrameHeight() const
{
	return m_FrameHeight;
}

void Sprite::Draw() const
{
	m_pTexture->Draw(Point2f(), m_TextureClip);
}

void Sprite::Update()
{
	const float frameTime
	{
		m_pCurrentAnimation->m_HoldFirstFrame && m_CurrentFrame == 0
		? m_pCurrentAnimation->m_HoldTime
		: 1.0f / m_pCurrentAnimation->m_NrFramesPerSec
	};

	m_FrameAccuSec += Time::deltaTime;
	if (m_FrameAccuSec >= frameTime)
	{
		m_CurrentFrame = (m_CurrentFrame + 1) % m_pCurrentAnimation->m_NrFrames;
		m_FrameAccuSec = 0.0f;

		UpdateTextClip();
	}
}

void Sprite::SetAnimation(const std::string animName)
{
	if (animName == m_pCurrentAnimation->m_AnimName) return;

	for (Animation* ptr : m_pAnimations)
	{
		if (ptr->m_AnimName == animName)
		{
			m_CurrentFrame = 0;
			m_pCurrentAnimation = ptr;
		}
	}
}

void Sprite::SetSprite()
{
	m_pAnimations.clear();

	switch (m_Type)
	{
	case SpriteType::player:
		m_pTexture = new Texture{ "Resources/Images/Sprite_Player.png" };
		m_SheetWidth = m_pTexture->GetWidth();
		m_SheetHeight = m_pTexture->GetHeight();
		m_FrameWidth = 18.0f;
		m_FrameHeight = 15.0f;

		m_pAnimations.push_back(new Animation("idle", 4, 5, 1, 4, 0, 0));
		m_pAnimations.push_back(new Animation("run", 4, 10, 1, 4, 1, 0));
		m_pAnimations.push_back(new Animation("jump_up", 1, 10, 1, 1, 0, 4));
		m_pAnimations.push_back(new Animation("jump_down", 1, 10, 1, 1, 1, 4));
		break;
	case SpriteType::crabEnemy:
		m_pTexture = new Texture{ "Resources/Images/Sprite_Crab.png" };
		m_SheetWidth = m_pTexture->GetWidth();
		m_SheetHeight = m_pTexture->GetHeight();
		m_FrameWidth = m_SheetWidth / 3.0f;
		m_FrameHeight = m_SheetHeight;

		m_pAnimations.push_back(new Animation("walk", 3, 6, 1, 3, 0, 0));
		break;
	case SpriteType::damageBlock:
		m_pTexture = new Texture{ "Resources/Images/Sprite_Damageblock.png" };
		m_SheetWidth = m_pTexture->GetWidth();
		m_SheetHeight = m_pTexture->GetHeight();
		m_FrameWidth = 8.0f;
		m_FrameHeight = 8.0f;

		m_pAnimations.push_back(new Animation("shine", 9, 15, 3, 4, 0, 0, true)); 
	break;
	case SpriteType::risingHand:
		m_pTexture = new Texture{ "Resources/Images/Sprite_RisingHand.png" };
		m_SheetWidth = m_pTexture->GetWidth();
		m_SheetHeight = m_pTexture->GetHeight();
		m_FrameWidth = 16.0f;
		m_FrameHeight = 18.0f;

		m_pAnimations.push_back(new Animation("idle", 1, 2, 1, 1, 0, 0));
		m_pAnimations.push_back(new Animation("extended", 1, 2, 1, 1, 0, 1));
		m_pAnimations.push_back(new Animation("grabbing", 1, 60, 1, 1, 0, 2));
		break;
	default:
		break;
	}

	m_FrameAccuSec = 0.0f;
	m_CurrentFrame = 0;
	m_pCurrentAnimation = m_pAnimations[0];

	m_TextureClip = Rectf
	{
		0.0f,
		0.0f,
		m_FrameWidth,
		m_FrameHeight
	};

	UpdateTextClip();
}

void Sprite::UpdateTextClip()
{
	const int widthIndex{ m_CurrentFrame % m_pCurrentAnimation->m_NrCols };
	const int heightIndex{ m_CurrentFrame / m_pCurrentAnimation->m_NrCols + 1 };

	m_TextureClip.left = widthIndex * m_FrameWidth + (m_pCurrentAnimation->m_ColOffset * m_FrameWidth);
	m_TextureClip.bottom = heightIndex * m_FrameHeight + (m_pCurrentAnimation->m_RowOffset * m_FrameHeight);
}
