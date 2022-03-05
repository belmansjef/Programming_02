#pragma once
#include "Texture.h"

class Sprite
{
public:
	enum class SpriteType
	{
		player,
		crab,
		bat,
		hazard
	};

	Sprite(const SpriteType& type);
	~Sprite();

	void Draw() const;
	void Update(float elapsedSec);
	void SetType(const SpriteType& type);

private:
	SpriteType m_Type;
	Texture* m_pTexture;
	Rectf m_TextureClip;
	float m_SheetWidth;
	float m_SheetHeight;
	float m_FrameWidth;
	float m_FrameHeight;

	int m_NrRows;
	int m_NrCols;
	int m_NrFrames;
	int m_NrFramesPerSec;
	int m_CurrentFrame;
	float m_FrameAccuSec;

	void UpdateSprite();
};

