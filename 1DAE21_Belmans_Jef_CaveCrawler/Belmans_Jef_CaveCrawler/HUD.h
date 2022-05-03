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

	static void UpdateHealth(int newHealth);
	void Draw() const;

private:
	Texture* m_pTexHealthBar;
	Point2f m_BottomLeft;
	static Rectf m_SrcRect;

	const float m_HealthUIScale{ 3 };
};

