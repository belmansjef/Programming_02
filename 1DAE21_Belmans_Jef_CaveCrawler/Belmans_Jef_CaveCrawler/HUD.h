#pragma once
#include "pch.h"
#include "Texture.h"

class HUD final
{
public:
	HUD(const Window& window, int maxHealth);
	~HUD();

	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& other) = delete;

	static Rectf m_SrcRect;
	static void UpdateHealth(int newHealth);

	void UpdateScore(int newScore);
	void Draw() const;

private:
	const float m_HealthUIScale{ 3 };
	const float m_WindowWidth;
	const float m_WindowHeight;
	float m_PaddingLeft;
	float m_PaddingTop;

	Texture* m_pTexHealthBar;
	Texture* m_pScoreText;

	Point2f m_PosHealthBar;
	Point2f m_PosScoreText; 
	Rectf m_ScoreBackground;
};

