#pragma once
#include "MenuBase.h"
class GameFinishedMenu final : public MenuBase
{
public:
	GameFinishedMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight);
	~GameFinishedMenu();

	GameFinishedMenu(const GameFinishedMenu& other) = delete;
	GameFinishedMenu& operator=(const GameFinishedMenu& other) = delete;
	GameFinishedMenu(GameFinishedMenu&& other) = delete;
	GameFinishedMenu& operator=(GameFinishedMenu&& other) = delete;

	virtual void Enter(Game& game) override;
	virtual void Draw() const override;

	void SetScoreText(int currentScore, int highScore);

private:
	Button* m_pMenuButton;
	Texture* m_pScoreText;
	Texture* m_pHighScoreText;

	const float m_WindowWidth;
	Point2f m_PosScoreText;
	Point2f m_PosHighScoreText;
};