#include "LevelFinishedMenu.h"
#include "Button.h"
#include "Game.h"
#include "Enums.h"

LevelFinishedMenu::LevelFinishedMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight)
	: MenuBase("LEVEL FINISHED", 52, windowWidth, windowHeight, bottomLeft)
	, m_pNextLevelButton{ new Button(Point2f(), "NEXT LVL")}
	, m_pMenuButton { new Button(Point2f(), "MENU")}
{
	AddButton(m_pNextLevelButton);
	AddButton(m_pMenuButton);

	FitButtonsToPanel();
}

LevelFinishedMenu::~LevelFinishedMenu()
{
	m_pNextLevelButton = nullptr;
	m_pMenuButton = nullptr;
}

void LevelFinishedMenu::Enter(Game& game)
{
	MenuBase::Enter(game);

	if (IsActive())
	{
		Button* pHighlightedButton = GetHighlightedButton();
		if (pHighlightedButton == m_pNextLevelButton)
		{
			game.SetGameState(GameState::InGame);
			game.LoadNextLevel();
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