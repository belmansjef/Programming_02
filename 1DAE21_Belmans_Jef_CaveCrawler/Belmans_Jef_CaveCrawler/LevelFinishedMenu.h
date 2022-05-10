#pragma once
#include "MenuBase.h"

class LevelFinishedMenu final : public MenuBase
{
public:
	LevelFinishedMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight);
	~LevelFinishedMenu();

	LevelFinishedMenu(const LevelFinishedMenu& other) = delete;
	LevelFinishedMenu& operator=(const LevelFinishedMenu& other) = delete;
	LevelFinishedMenu(LevelFinishedMenu&& other) = delete;
	LevelFinishedMenu& operator=(LevelFinishedMenu&& other) = delete;

	virtual void Enter(Game& game) override;

private:
	Button* m_pRestartButton;
	Button* m_pMenuButton;
};

