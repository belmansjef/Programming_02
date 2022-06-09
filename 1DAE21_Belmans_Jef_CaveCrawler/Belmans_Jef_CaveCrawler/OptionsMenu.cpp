#include "pch.h"
#include "OptionsMenu.h"
#include "Button.h"
#include "Texture.h"
#include "SoundManager.h"
#include "Game.h"
#include <sstream>
#include <iomanip>

OptionsMenu::OptionsMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight )
	: MenuBase("OPTIONS", 52, windowWidth, windowHeight, bottomLeft)
	, m_pVolumeUpButton{ new Button(Point2f(80.0f, 168.0f), "UP", 16, 40.0f)}
	, m_pVolumeDownButton{ new Button(Point2f(220.0f, 168.0f), "DN", 16, 40.0f)}
	, m_pMenuButton{ new Button(Point2f(80.0f, 108.0f), "MENU") }
	, m_pVolumeText { nullptr }
{
	SetVolumeText();

	AddButton(m_pVolumeUpButton);
	AddButton(m_pVolumeDownButton);
	AddButton(m_pMenuButton);
}

OptionsMenu::~OptionsMenu()
{
	delete m_pVolumeText;
	m_pVolumeText = nullptr;
	m_pVolumeDownButton = nullptr;
	m_pVolumeUpButton = nullptr;
	m_pMenuButton = nullptr;
}

void OptionsMenu::Draw() const
{
	MenuBase::Draw();
	m_pVolumeText->Draw(m_PosVolumeText);
}

void OptionsMenu::Enter(Game& game)
{
	MenuBase::Enter(game);

	if (IsActive())
	{
		Button* pHighlightedButton = GetHighlightedButton();
		if (pHighlightedButton == m_pVolumeUpButton)
		{
			ChangeVolume(true);
		}
		else if (pHighlightedButton == m_pVolumeDownButton)
		{
			ChangeVolume(false);
		}
		else if (pHighlightedButton == m_pMenuButton)
		{
			game.BackToMainMenu();
			Close();
		}
	}
}

void OptionsMenu::ChangeVolume(bool up)
{
	//SoundManager::GetInstance()->AdjustVolume(up ? 20.0f : -20.0f);
	SetVolumeText();
}

void OptionsMenu::SetVolumeText()
{
	std::stringstream ss;
	//ss << std::setprecision(2) << "VOL " << SoundManager::GetInstance()->GetVolume();

	delete m_pVolumeText;
	m_pVolumeText = new Texture(ss.str(), "Resources/Font.ttf", 16, Color4f(1.0f, 1.0f, 1.0f, 1.0f));

	m_PosVolumeText = Point2f
	(
		170.0f - m_pVolumeText->GetWidth() / 2.0f,
		188.0f - m_pVolumeText->GetHeight() / 2.0f
	);
}
