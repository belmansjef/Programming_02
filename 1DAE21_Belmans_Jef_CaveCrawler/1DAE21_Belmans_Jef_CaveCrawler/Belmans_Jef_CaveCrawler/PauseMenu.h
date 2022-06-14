#pragma once
#include "MenuBase.h"

class PauseMenu final : public MenuBase
{
public:
	PauseMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight);
	~PauseMenu();

	PauseMenu(const PauseMenu& other) = delete;
	PauseMenu& operator=(const PauseMenu& other) = delete;
	PauseMenu(PauseMenu&& other) = delete;
	PauseMenu& operator=(PauseMenu&& other) = delete;

	virtual void Enter(Game& game) override;
	
private:
	Button* m_pContinueButton;
	Button* m_pRestartButton;
	Button* m_pBackToMenuButton;
};

