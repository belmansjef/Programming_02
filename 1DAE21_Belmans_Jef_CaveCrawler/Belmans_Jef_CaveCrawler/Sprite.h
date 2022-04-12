#pragma once
#include <vector>
#include "pch.h"
#include "Texture.h"

struct Animation
{
	Animation();
	~Animation() = default;
	Animation(std::string animName, int nrFrames, int nrFramesPerSec, int nrRows, int nrCols, int rowOffset, int colOffset, bool holdLastFrame = false);
	Animation(const Animation& other) = delete;
	Animation& operator=(const Animation& other) = default;
	Animation(Animation&& other) = delete;
	Animation operator=(Animation&& other) = delete;
	
	std::string m_AnimName;
	int m_NrFrames;
	int m_NrFramesPerSec;
	int m_NrRows;
	int m_NrCols;
	int m_RowOffset;
	int m_ColOffset;
	bool m_HoldFirstFrame;
	float m_HoldTime;
};

enum class SpriteType
{
	player,
	damageBlock,
	risingHand
};

class Sprite
{
public:
	Sprite(const SpriteType& type);
	~Sprite();
	Sprite(const Sprite& other) = delete;
	Sprite& operator=(const Sprite& other) = delete;
	Sprite(Sprite&& other) = delete;
	Sprite& operator=(Sprite&& other) = delete;

	float GetFrameWidth() const;
	float GetFrameHeight() const;

	void Draw() const;
	void Update();
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
	std::vector<Animation*> m_pAnimations;

	void SetSprite();
	void UpdateTextClip();
};