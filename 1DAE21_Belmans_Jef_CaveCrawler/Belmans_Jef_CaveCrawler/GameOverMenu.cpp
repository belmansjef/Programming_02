#include "GameOverMenu.h"
#include "Button.h"
#include "Game.h"
#include "Enums.h"

GameOverMenu::GameOverMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight)
	: MenuBase("YOU DIED!", 52, windowWidth, windowHeight, bottomLeft)
	, m_pRestartButton { new Button(Point2f(), "RESTART") }
	, m_pMenuButton { new Button(Point2f(), "MENU") }
{
	AddButton(m_pRestartButton);
	AddButton(m_pMenuButton);

	FitButtonsToPanel();
}

GameOverMenu::~GameOverMenu()
{
	m_pRestartButton = nullptr;
	m_pMenuButton = nullptr;
}

void GameOverMenu::Enter(Game& game)
{
	MenuBase::Enter(game);

	if (IsActive())
	{
		Button* pHighlightedButton = GetHighlightedButton();
		if (pHighlightedButton == m_pRestartButton)
		{
			game.SetGameState(GameState::InGame);
			game.ResetLevel();
			Close();
		}
		else if (pHighlightedButton == m_pMenuButton)
		{
			game.LoadLevelByName("Level_1");
			game.BackToMainMenu();
		}

		Time::GetInstance()->m_TimeScale = 1.0f;
	}
}
