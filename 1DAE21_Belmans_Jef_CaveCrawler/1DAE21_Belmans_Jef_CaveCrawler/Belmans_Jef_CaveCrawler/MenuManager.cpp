#include "MenuManager.h"
#include "MainMenu.h"
#include "OptionsMenu.h"
#include "PauseMenu.h"
#include "LevelFinishedMenu.h"
#include "GameFinishedMenu.h"
#include "GameOverMenu.h"
#include "SoundManager.h"
#include "Enums.h"
#include "ScoreManager.h"

MenuManager::MenuManager(float windowWidth, float windowHeight)
	: m_pActiveMenu { nullptr }
	, m_pMainMenu{ new MainMenu(Point2f(80.0f, 108.0f), windowWidth, windowHeight) }
	, m_pOptionsMenu { new OptionsMenu(Point2f(80.0f, 108.0f), windowWidth, windowHeight) }
	, m_pPauseMenu{ new PauseMenu(Point2f(80.0f, 108.0f), windowWidth, windowHeight) }
	, m_pLevelFinishedMenu { new LevelFinishedMenu(Point2f(80.0f, 108.0f), windowWidth, windowHeight)}
	, m_pGameOverMenu{ new GameOverMenu(Point2f(80.0f, 108.0f), windowWidth, windowHeight)}
	, m_pGameFinishedMenu { new GameFinishedMenu(Point2f(80.0f, 108.0f), windowWidth, windowHeight)}
{
	OpenMenu(MenuType::Main);
}

MenuManager::~MenuManager()
{
	delete m_pMainMenu;
	delete m_pOptionsMenu;
	delete m_pPauseMenu;
	delete m_pGameOverMenu;
	delete m_pLevelFinishedMenu;
	delete m_pGameFinishedMenu;

	m_pActiveMenu = nullptr;
	m_pMainMenu = nullptr;
	m_pOptionsMenu = nullptr;
	m_pPauseMenu = nullptr;
	m_pGameOverMenu = nullptr;
	m_pLevelFinishedMenu = nullptr;
	m_pGameFinishedMenu = nullptr;
}

void MenuManager::CycleSelection(bool up)
{
	m_pActiveMenu->CycleSelection(up);
}

void MenuManager::Enter(Game& game)
{
	m_pActiveMenu->Enter(game);
}

void MenuManager::OpenMenu(const MenuType& menu)
{
	if (m_pActiveMenu != nullptr)
	{
		m_pActiveMenu->Close();
	}

	switch (menu)
	{
	case MenuType::Main:
		m_pActiveMenu = m_pMainMenu;
		break;
	case MenuType::Options:
		m_pActiveMenu = m_pOptionsMenu;
		break;
	case MenuType::Pause:
		m_pActiveMenu = m_pPauseMenu;
		break;
	case MenuType::GameOver:
		m_pActiveMenu = m_pGameOverMenu;
		break;
	case MenuType::Finished:
		m_pActiveMenu = m_pLevelFinishedMenu;
		break;
	case MenuType::GameFinished:
		m_pActiveMenu = m_pGameFinishedMenu;
		break;
	default:
		break;
	}

	m_pActiveMenu->Open();
}

void MenuManager::DrawActiveMenu() const
{
	if (m_pActiveMenu != nullptr)
	{
		m_pActiveMenu->Draw();
	}
}

void MenuManager::SetScoreText(const ScoreManager& scoreManager)
{
	m_pGameFinishedMenu->SetScoreText(scoreManager.GetCurrentScore(), scoreManager.GetHighScore());
}
