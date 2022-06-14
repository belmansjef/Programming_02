#pragma once
#include <vector>
#include "structs.h"

enum class SpriteType;
class Texture;

struct Animation final
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

class Sprite final
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

	void Update();
	void Draw() const;
	void SetAnimation(const std::string& animName);
	void FlashSprite();

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

	const float m_FlashDuration;
	const int m_TotalFlashes;
	float m_LastFlashTime;
	int m_CurrentFlashes;
	bool m_DoFlash;
	bool m_DoChangeColor;

	Animation* m_pCurrentAnimation;
	std::vector<Animation*> m_pAnimations;

	void SetSprite();
	void UpdateTextClip();
};