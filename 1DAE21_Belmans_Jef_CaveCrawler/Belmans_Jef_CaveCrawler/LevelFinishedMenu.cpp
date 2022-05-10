#include "LevelFinishedMenu.h"
#include "Button.h"
#include "Game.h"

LevelFinishedMenu::LevelFinishedMenu(const Point2f& buttonPanelBottomLeft, float windowWidth, float windowHeight)
	: MenuBase("LEVEL FINISHED", 52, windowWidth, windowHeight, Rectf(buttonPanelBottomLeft.x, buttonPanelBottomLeft.y, 100.0f, 120.0f))
	, m_pRestartButton{ new Button(Point2f(), "RESTART")}
	, m_pMenuButton { new Button(Point2f(), "MENU")}
{
	AddButton(m_pRestartButton);
	AddButton(m_pMenuButton);

	FitButtonsToPanel();
}

LevelFinishedMenu::~LevelFinishedMenu()
{
	m_pRestartButton = nullptr;
	m_pMenuButton = nullptr;
}

void LevelFinishedMenu::Enter(Game& game)
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
			game.ResetLevel();
			game.BackToMainMenu();
		}

		Time::SetTimeScale(1.0f);
	}
}