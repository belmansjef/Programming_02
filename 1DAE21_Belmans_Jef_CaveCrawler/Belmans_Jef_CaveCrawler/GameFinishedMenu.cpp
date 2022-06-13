#include "GameFinishedMenu.h"
#include "pch.h"
#include "Button.h"
#include "Texture.h"
#include "Game.h"
#include "Time.h"
#include <sstream>

GameFinishedMenu::GameFinishedMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight)
	: MenuBase("GAME FINISHED", 52, windowWidth, windowHeight, bottomLeft)
	, m_pMenuButton{ new Button(Point2f(), "MENU") }
	, m_pScoreText { new Texture("SCORE 1425", "Resources/Font.ttf", 40, Color4f(1.0f, 1.0f, 1.0f, 1.0f))}
	, m_pHighScoreText{ new Texture("HIGHSCORE 1575", "Resources/Font.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 0.7f)) }
	, m_PosScoreText { windowWidth / 2.0f - m_pScoreText->GetWidth() / 2.0f, windowHeight / 2.0f}
	, m_PosHighScoreText { windowWidth / 2.0f - m_pHighScoreText->GetWidth() / 2.0f, m_PosScoreText.y - m_pHighScoreText->GetHeight() - 32.0f}
	, m_WindowWidth { windowWidth }
{
	AddButton(m_pMenuButton);

	FitButtonsToPanel();
}

GameFinishedMenu::~GameFinishedMenu()
{
	delete m_pScoreText;
	delete m_pHighScoreText;

	m_pMenuButton = nullptr;
	m_pScoreText = nullptr;
	m_pHighScoreText = nullptr;
}

void GameFinishedMenu::Enter(Game& game)
{
	MenuBase::Enter(game);

	if (IsActive())
	{
		Button* pHighlightedButton = GetHighlightedButton();
		if (pHighlightedButton == m_pMenuButton)
		{
			game.LoadLevelByName("Level_1");
			game.BackToMainMenu();
		}

		Time::GetInstance()->m_TimeScale = 1.0f;
	}
}

void GameFinishedMenu::Draw() const
{
	MenuBase::Draw();
	m_pScoreText->Draw(m_PosScoreText);
	m_pHighScoreText->Draw(m_PosHighScoreText);
}

void GameFinishedMenu::SetScoreText(int currentScore, int highScore)
{
	delete m_pScoreText;
	std::stringstream ss{};
	ss << "SCORE " << currentScore;
	m_pScoreText = new Texture(ss.str(), "Resources/Font.ttf", 40, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_PosScoreText.x = (m_WindowWidth / 2.0f) - (m_pScoreText->GetWidth() / 2.0f);

	ss.str(std::string());
	delete m_pHighScoreText;
	ss << "HIGHSCORE " << highScore;
	m_pHighScoreText = new Texture(ss.str(), "Resources/Font.ttf", 32, Color4f(1.0f, 1.0f, 1.0f, 0.7f));
	m_PosHighScoreText.x = (m_WindowWidth / 2.0f) - (m_pHighScoreText->GetWidth() / 2.0f);
}
