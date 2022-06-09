#include "Sprite.h"
#include "pch.h"
#include "Texture.h"
#include "Enums.h"

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
	, m_FlashDuration { 0.1f }
	, m_TotalFlashes { 3 }
	, m_DoFlash { false }
	, m_DoChangeColor { false }
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
	m_pTexture->Draw(Point2f(), m_TextureClip, m_DoChangeColor);
}

void Sprite::Update()
{
	const float frameTime
	{
		m_pCurrentAnimation->m_HoldFirstFrame && m_CurrentFrame == 0
		? m_pCurrentAnimation->m_HoldTime
		: 1.0f / m_pCurrentAnimation->m_NrFramesPerSec
	};

	//m_FrameAccuSec += Time::GetInstance()->m_DeltaTime;
	if (m_FrameAccuSec >= frameTime)
	{
		m_CurrentFrame = (m_CurrentFrame + 1) % m_pCurrentAnimation->m_NrFrames;
		m_FrameAccuSec = 0.0f;

		UpdateTextClip();
	}

	if (m_DoFlash)
	{
		/*if (m_LastFlashTime + m_FlashDuration < Time::GetInstance()->m_Time)
		{
			m_DoChangeColor = !m_DoChangeColor;
			m_CurrentFlashes++;
			
			m_LastFlashTime = Time::GetInstance()->m_Time;
			if (m_CurrentFlashes >= m_TotalFlashes)
			{
				m_DoFlash = m_DoChangeColor = false;
			}
		}*/
	}
}

void Sprite::SetAnimation(const std::string& animName)
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

void Sprite::FlashSprite()
{
	m_CurrentFlashes = 0;
	m_DoFlash = m_DoChangeColor = true;
	//m_LastFlashTime = Time::GetInstance()->m_Time;
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
	case SpriteType::cannonEnemyBase:
		m_pTexture = new Texture{ "Resources/Images/Sprite_TurretBase.png" };
		m_SheetWidth = m_pTexture->GetWidth();
		m_SheetHeight = m_pTexture->GetHeight();
		m_FrameWidth = m_SheetWidth;
		m_FrameHeight = m_SheetHeight;

		m_pAnimations.push_back(new Animation("idle", 1, 60, 1, 1, 0, 0));
		break;
	case SpriteType::cannonEnemyBarrel:
		m_pTexture = new Texture{ "Resources/Images/Sprite_TurretBarrel.png" };
		m_SheetWidth = m_pTexture->GetWidth();
		m_SheetHeight = m_pTexture->GetHeight();
		m_FrameWidth = m_SheetWidth / 2.0f;
		m_FrameHeight = m_SheetHeight;

		m_pAnimations.push_back(new Animation("idle", 1, 60, 1, 1, 0, 1));
		m_pAnimations.push_back(new Animation("shot", 1, 60, 1, 1, 0, 0));
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

		m_pAnimations.push_back(new Animation("idle", 1, 60, 1, 1, 0, 0));
		m_pAnimations.push_back(new Animation("extended", 1, 60, 1, 1, 0, 1));
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
