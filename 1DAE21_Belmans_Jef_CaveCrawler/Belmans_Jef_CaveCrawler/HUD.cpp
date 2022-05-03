#include "HUD.h"

HUD::HUD(const Window& window)
	: m_pTexHealthBar { new Texture("Resources/Images/UI_Healthbar.png")}
{
	float paddingTop{ m_pTexHealthBar->GetHeight() / m_MaxHealth + 32.0f };
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
		m_pTexHealthBar->GetHeight() / (m_MaxHealth + 1)
	};
}

HUD::~HUD()
{
	delete m_pTexHealthBar;
	m_pTexHealthBar = nullptr;
}

void HUD::Update(int currentHealth)
{
	m_CurrentHealth = currentHealth;

	m_SrcRect.bottom = m_SrcRect.height * (m_CurrentHealth + 1);
}

void HUD::Draw() const
{
	glPushMatrix();
		glTranslatef(m_BottomLeft.x, m_BottomLeft.y, 0);
		glScalef(3, 3, 0);
		m_pTexHealthBar->Draw(Point2f(), m_SrcRect);
	glPopMatrix();
}
