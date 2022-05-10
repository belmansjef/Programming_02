#include <stdlib.h>
#include "MainMenu.h"
#include "Game.h"
#include "Button.h"
#include "SoundManager.h"

MainMenu::MainMenu(const Point2f& buttonPanelBottomLeft, const Window& window)
	: MenuBase("CAVE CRAWLER", 52, window, Rectf(buttonPanelBottomLeft.x, buttonPanelBottomLeft.y, 100.0f, 180.0f))
	, m_pStartButton{ new Button(Point2f(), "START")}
	, m_pOptionsButton{ new Button(Point2f(), "OPTIONS") }
	, m_pExitButton{ new Button(Point2f(), "EXIT") }
{
	AddButton(m_pStartButton);
	AddButton(m_pOptionsButton);
	AddButton(m_pExitButton);

	FitButtonsToPanel();
}


MainMenu::~MainMenu()
{
	m_pStartButton = nullptr;
	m_pOptionsButton = nullptr;
	m_pExitButton = nullptr;
}

void MainMenu::Enter(Game& game)
{
	SoundManager::GetInstance()->PlaySound(SoundType::enterUI);
	if (m_pHighlightedButton == m_pStartButton)
	{
		game.SetGameState(GameState::InGame);
		Close();
	}
	else if (m_pHighlightedButton == m_pOptionsButton)
	{
		// TODO: open options
	}
	else if (m_pHighlightedButton == m_pExitButton)
	{
		exit(0);	
	}
}
