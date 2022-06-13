#include "HUD.h"
#include "utils.h"
#include "ScoreManager.h"

// Statics
Rectf HUD::m_SrcRect{ Rectf() };
void HUD::UpdateHealth(int newHealth)
{
	m_SrcRect.bottom = m_SrcRect.height * (newHealth + 1);
}

HUD::HUD(const Window& window, int maxHealth)
	: m_pTexHealthBar { new Texture("Resources/Images/UI_Healthbar.png")}
	, m_pScoreText { new Texture { "0000", "Resources/Font.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f)} }
	, m_WindowWidth { window.width }
	, m_WindowHeight { window.height }
	, m_PaddingLeft { 16.0f }
	, m_PaddingTop { 0.0f }
	, m_ScoreBackground{}
{
	m_PaddingTop = (m_pTexHealthBar->GetHeight() / maxHealth) * m_HealthUIScale;

	m_PosHealthBar = Point2f
	{
		m_PaddingLeft,
		window.height - m_PaddingTop
	};

	m_PosScoreText = Point2f
	{
		window.width - m_PaddingLeft - m_pScoreText->GetWidth(),
		window.height - m_PaddingTop
	};

	m_ScoreBackground = Rectf
	{
		m_PosScoreText.x - 10.0f,
		m_PosScoreText.y - 5.0f,
		150.0f,
		m_pScoreText->GetHeight() + 10.0f
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


void HUD::UpdateScore(int newScore)
{
	delete m_pScoreText;
	m_pScoreText = new Texture{ std::to_string(newScore), "Resources/Font.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f) };

	m_PosScoreText = Point2f
	{
		m_WindowWidth - m_PaddingLeft - m_pScoreText->GetWidth(),
		m_WindowHeight - m_PaddingTop
	};

	m_ScoreBackground = Rectf
	{
		m_PosScoreText.x - 10.0f,
		m_PosScoreText.y - 5.0f,
		150.0f,
		m_pScoreText->GetHeight() + 10.0f
	};
}

void HUD::Draw() const
{
	glPushMatrix();
		glTranslatef(m_PosHealthBar.x, m_PosHealthBar.y, 0);
		glScalef(m_HealthUIScale, m_HealthUIScale, 0);
		m_pTexHealthBar->Draw(Point2f(), m_SrcRect);
	glPopMatrix();

	utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 0.75f));
	utils::FillRect(m_ScoreBackground);

	glPushMatrix();
		glTranslatef(m_PosScoreText.x, m_PosScoreText.y, 0);
		m_pScoreText->Draw();
	glPopMatrix();
}

