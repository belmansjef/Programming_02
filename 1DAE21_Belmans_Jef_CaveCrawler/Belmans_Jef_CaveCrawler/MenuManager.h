#pragma once

enum class MenuType;
class MenuBase;
class MainMenu;
class OptionsMenu;
class PauseMenu;
class GameOverMenu;
class LevelFinishedMenu;
class Game;

class MenuManager final
{
public:
	MenuManager(float windowWidth = 1024.0f, float windowHeight = 576.0f);
	~MenuManager();

	void CycleSelection(bool up);
	void Enter(Game& game);
	void OpenMenu(const MenuType& menu);
	void DrawActiveMenu() const;

private:
	MenuBase* m_pActiveMenu;

	MainMenu* m_pMainMenu;
	OptionsMenu* m_pOptionsMenu;
	PauseMenu* m_pPauseMenu;
	GameOverMenu* m_pGameOverMenu;
	LevelFinishedMenu* m_pLevelFinishedMenu;
};

