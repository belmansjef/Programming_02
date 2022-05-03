#include "HUD.h"

// Statics
Rectf HUD::m_SrcRect{ Rectf() };
void HUD::UpdateHealth(int newHealth)
{
	m_SrcRect.bottom = m_SrcRect.height * (newHealth + 1);
}

HUD::HUD(const Window& window, int maxHealth)
	: m_pTexHealthBar { new Texture("Resources/Images/UI_Healthbar.png")}
{
	float paddingTop{ (m_pTexHealthBar->GetHeight() / maxHealth) * m_HealthUIScale };
	float paddingLeft{ 16.0f };

	m_BottomLeft = Point2f
	{
		paddingLeft,
		window.height - paddingTop
	};

	m_SrcRect = Rectf
	{
		0.0f,
		0.0f,
		m_pTexHealthBar->GetWidth(),
		m_pTexHealthBar->GetHeight() / (maxHealth + 1)
	};
}

HUD::~HUD()
{
	delete m_pTexHealthBar;
	m_pTexHealthBar = nullptr;
}

void HUD::Draw() const
{
	glPushMatrix();
		glTranslatef(m_BottomLeft.x, m_BottomLeft.y, 0);
		glScalef(m_HealthUIScale, m_HealthUIScale, 0);
		m_pTexHealthBar->Draw(Point2f(), m_SrcRect);
	glPopMatrix();
}

