#pragma once
#include "MenuBase.h"

class GameOverMenu final : public MenuBase
{
public:
	GameOverMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight);
	~GameOverMenu();

	GameOverMenu(const GameOverMenu& other) = delete;
	GameOverMenu& operator=(const GameOverMenu& other) = delete;
	GameOverMenu(GameOverMenu&& other) = delete;
	GameOverMenu& operator=(GameOverMenu&& other) = delete;

	virtual void Enter(Game& game) override;

private:
	Button* m_pRestartButton;
	Button* m_pMenuButton;
};

