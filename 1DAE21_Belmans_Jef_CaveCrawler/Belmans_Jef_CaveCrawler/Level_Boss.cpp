#include "Level_Boss.h"

Level_Boss::Level_Boss(const Window& window)
	: LevelBase::LevelBase("Level_Boss", window, Point2f(88.0f, 32.0f), Point2f(740.0f, 32.0f), "Resources/Images/Level_Boss.png", "Resources/Images/Level_Boss.svg")
	, m_BossManager { 396.0f, 32.0f, window }
{
	m_CameraZoneManager.Initialize("Resources/Initializers/CameraZones_BossLevel.txt");
}

void Level_Boss::Reset()
{
	LevelBase::Reset();
	m_BossManager.Reset();
}

void Level_Boss::Draw(const GameState& currentGameState) const
{
	LevelBase::Draw(currentGameState);
	glPushMatrix();
		glScalef(m_ScaleFactor, m_ScaleFactor, 1);
		m_Camera.Transform();
		m_BossManager.Draw();
	glPopMatrix();
	
	m_BossManager.DrawHUD();
}

void Level_Boss::Update(GameState& currentGameState, MenuManager& menuManager)
{
	LevelBase::Update(currentGameState, menuManager);
	m_BossManager.Update(m_PlayerAvatar, *this, currentGameState);
}
