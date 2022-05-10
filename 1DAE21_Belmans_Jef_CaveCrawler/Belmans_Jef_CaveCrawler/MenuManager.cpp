#include "MenuManager.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "LevelFinishedMenu.h"

MenuManager::MenuManager(float windowWidth, float windowHeight)
	: m_pActiveMenu { nullptr }
	, m_pMainMenu{ new MainMenu(Point2f(80.0f, 50.0f), windowWidth, windowHeight) }
	, m_pPauseMenu{ new PauseMenu(Point2f(80.0f, 50.0f), windowWidth, windowHeight) }
	, m_pLevelFinishedMenu { new LevelFinishedMenu(Point2f(80.0f, 50.0f), windowWidth, windowHeight)}
{
	OpenMenu(MenuType::Main);
}

MenuManager::~MenuManager()
{
	delete m_pMainMenu;
	// delete m_pOptionsMenu;
	delete m_pPauseMenu;
	// delete m_pDeathMenu;
	delete m_pLevelFinishedMenu;

	m_pActiveMenu = nullptr;
	m_pMainMenu = nullptr;
	// m_pOptionsMenu = nullptr;
	m_pPauseMenu = nullptr;
	// m_pDeathMenu = nullptr;
	m_pLevelFinishedMenu = nullptr;
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
		break;
	case MenuType::Pause:
		m_pActiveMenu = m_pPauseMenu;
		break;
	case MenuType::Finished:
		m_pActiveMenu = m_pLevelFinishedMenu;
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
