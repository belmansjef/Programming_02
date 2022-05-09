#pragma once
#include "MenuBase.h"


class MainMenu final : public MenuBase
{
public:

	virtual void Enter(Game* game) override;

private:
	Button* m_pStartButton;
	Button* m_pOptionsButton;
	Button* m_pExitButton;
};

