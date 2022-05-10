#include "PauseMenu.h"
#include "Game.h"
#include "Button.h"
#include "SoundManager.h"

PauseMenu::PauseMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight)
	: MenuBase("PAUSED", 52, windowWidth, windowHeight, bottomLeft)
	, m_pContinueButton { new Button(Point2f(), "CONTINUE") }
	, m_pRestartButton { new Button(Point2f(), "RESTART") }
	, m_pBackToMenuButton { new Button(Point2f(), "MENU") }
{
	AddButton(m_pContinueButton);
	AddButton(m_pRestartButton);
	AddButton(m_pBackToMenuButton);

	FitButtonsToPanel();
}

PauseMenu::~PauseMenu()
{
	m_pContinueButton = nullptr;
	m_pRestartButton = nullptr;
	m_pBackToMenuButton = nullptr;
}

void PauseMenu::Enter(Game& game)
{
	MenuBase::Enter(game);

	if (IsActive())
	{
		Button* pHighlightedButton = GetHighlightedButton();
		if (pHighlightedButton == m_pContinueButton)
		{
			game.SetGameState(GameState::InGame);
			Close();
		}
		else if (pHighlightedButton == m_pRestartButton)
		{
			game.SetGameState(GameState::InGame);
			game.ResetLevel();
			Close();
		}
		else if (pHighlightedButton == m_pBackToMenuButton)
		{
			game.SetGameState(GameState::MainMenu);
			game.ResetLevel();
			game.BackToMainMenu();
		}

		Time::SetTimeScale(1.0f);
	}
}
