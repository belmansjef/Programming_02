#include "HUD.h"
#include "Texture.h"

HUD::HUD(const Point2f& bottomLeft, int totalPowerUps)
	: m_BottomLeft { bottomLeft }
	, m_TotalPowerUps{ totalPowerUps }
	, m_HitPowerUps { 0 }
	, m_pLeftTexture{ new Texture("./Resources/Images/HudLeft.png")}
	, m_pRightTexture{ new Texture("./Resources/Images/HudRight.png")}
	, m_pPowerUpTexture{ new Texture("./Resources/Images/HudPowerUp.png")}
	, m_HitSrcRect {0.0f, 0.0f, m_pPowerUpTexture->GetWidth() / 2.0f, m_pPowerUpTexture->GetHeight()}
	, m_NoHitSrcRect{m_pPowerUpTexture->GetWidth() / 2.0f, 0.0f, m_pPowerUpTexture->GetWidth() / 2.0f, m_pPowerUpTexture->GetHeight()}
{

}

HUD::HUD(const HUD& other)
	: m_BottomLeft{ other.m_BottomLeft }
	, m_TotalPowerUps{ other.m_TotalPowerUps }
	, m_HitPowerUps{ other.m_HitPowerUps }
	, m_pLeftTexture{ new Texture("./Resources/Images/HudLeft.png") }
	, m_pRightTexture{ new Texture("./Resources/Images/HudRight.png") }
	, m_pPowerUpTexture{ new Texture("./Resources/Images/HudPowerUp.png") }
	, m_HitSrcRect{ other.m_HitSrcRect }
	, m_NoHitSrcRect{ other.m_NoHitSrcRect }
{

}

HUD::~HUD()
{
	delete m_pLeftTexture;
	delete m_pRightTexture;
	delete m_pPowerUpTexture;

	m_pLeftTexture = m_pRightTexture = m_pPowerUpTexture = nullptr;
}

void HUD::Draw() const
{
	glPushMatrix();
		// Left texture	
		glTranslatef(m_BottomLeft.x, m_BottomLeft.y, 0);
		m_pLeftTexture->Draw();
	
		// PowerUp textures
		for (size_t i = 1; i <= m_TotalPowerUps; i++)
		{
			i == 1 // Trasnlate model matrix
				? glTranslatef(m_pLeftTexture->GetWidth(), 0, 0)
				: glTranslatef(m_pPowerUpTexture->GetWidth() / 2.0f, 0, 0);

			// Has hit texture
			i <= m_HitPowerUps
				? m_pPowerUpTexture->Draw(Point2f(), m_HitSrcRect)
				: m_pPowerUpTexture->Draw(Point2f(), m_NoHitSrcRect);
		}

		// Right texture
		glTranslatef(m_pPowerUpTexture->GetWidth() / 2.0f, 0, 0);
		m_pRightTexture->Draw();
	glPopMatrix();
}

void HUD::PowerUpHit()
{
	m_HitPowerUps++;
}

void HUD::SetTotalPowerUps(int totalPowerUps)
{
	m_TotalPowerUps = totalPowerUps;
}
