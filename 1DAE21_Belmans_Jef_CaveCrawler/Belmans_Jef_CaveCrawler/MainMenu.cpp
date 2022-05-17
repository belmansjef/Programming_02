#include <stdlib.h>
#include "MainMenu.h"
#include "Game.h"
#include "Button.h"
#include "SoundManager.h"

MainMenu::MainMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight)
	: MenuBase("CAVE CRAWLER", 52, windowWidth, windowHeight, bottomLeft)
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
	MenuBase::Enter(game);

	if (IsActive())
	{
		Button* pHighlightedButton = GetHighlightedButton();
		if (pHighlightedButton == m_pStartButton)
		{
			game.SetGameState(GameState::InGame);
			Close();
		}
		else if (pHighlightedButton == m_pOptionsButton)
		{
			game.OpenOptionsMenu();
			Close();
		}
		else if (pHighlightedButton == m_pExitButton)
		{
			game.SetDoQuit(true);
		}
	}
}
