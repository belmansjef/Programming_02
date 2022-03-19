#pragma once
#include "pch.h"

class Texture;
class HUD
{
public:
	HUD(const Point2f& bottomLeft, int totalPowerUps);
	~HUD();
	void Draw() const;
	void PowerUpHit();

	void SetTotalPowerUps(int totalPowerUps);

private:
	Point2f m_BottomLeft;
	int m_TotalPowerUps;
	int m_HitPowerUps;
	Texture* m_pLeftTexture;
	Texture* m_pRightTexture;
	Texture* m_pPowerUpTexture;

	const Rectf m_HitSrcRect;
	const Rectf m_NoHitSrcRect;
};

