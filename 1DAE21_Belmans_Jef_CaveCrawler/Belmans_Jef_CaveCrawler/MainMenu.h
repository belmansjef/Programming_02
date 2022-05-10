#pragma once
#include "MenuBase.h"

class MainMenu final : public MenuBase
{
public:
	MainMenu(const Point2f& buttenPanelBottomLeft, const Window& window);
	~MainMenu();

	MainMenu(const MainMenu& other) = delete;
	MainMenu& operator=(const MainMenu& other) = delete;
	MainMenu(MainMenu&& other) = delete;
	MainMenu& operator=(MainMenu&& other) = delete;

	virtual void Enter(Game& game) override;

private:
	Button* m_pStartButton;
	Button* m_pOptionsButton;
	Button* m_pExitButton;
};

