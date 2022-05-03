#pragma once
#include "pch.h"
#include "Texture.h"

class HUD final
{
public:
	HUD(const Window& window );
	~HUD();

	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& other) = delete;

	void Update(int currentHealth);
	void Draw() const;

private:
	Texture* m_pTexHealthBar;
	Point2f m_BottomLeft;
	Rectf m_SrcRect;

	int m_MaxHealth{ 4 };
	int m_CurrentHealth{ m_MaxHealth };
};

