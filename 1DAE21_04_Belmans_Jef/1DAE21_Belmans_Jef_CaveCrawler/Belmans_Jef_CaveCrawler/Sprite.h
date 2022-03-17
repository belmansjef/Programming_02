#pragma once
#include <vector>
#include "pch.h"
#include "Texture.h"

struct Animation
{
	Animation();
	Animation(std::string animName, int nrFrames, int nrFramesPerSec, int nrRows, int nrCols, int rowOffset, int colOffset);

	
	std::string m_AnimName;
	int m_NrFrames;
	int m_NrFramesPerSec;
	int m_NrRows;
	int m_NrCols;
	int m_RowOffset;
	int m_ColOffset;
};

class Sprite
{
public:
	enum class SpriteType
	{
		player
	};

	Sprite(const SpriteType& type);
	~Sprite();

	void Draw() const;
	void Update(float elapsedSec);
	void SetType(const SpriteType& type);
	void SetAnimation(const std::string animName);

private:
	Texture* m_pTexture;
	SpriteType m_Type;
	Rectf m_TextureClip;
	float m_SheetWidth;
	float m_SheetHeight;
	float m_FrameWidth;
	float m_FrameHeight;

	int m_CurrentFrame;
	float m_FrameAccuSec;

	Animation* m_pCurrentAnimation;
	std::vector<Animation*> m_Animations;

	void UpdateSprite();
};