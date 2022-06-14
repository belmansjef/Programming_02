#include "Level_1.h"
#include "MenuManager.h"
#include "Enums.h"

Level_1::Level_1(const Window& window)
	: LevelBase::LevelBase("Level_1", window, Point2f( 88.0f, 40.0f), Point2f(48.0f, 248.0f), "Resources/Images/Level_1.png", "Resources/Images/Level_1.svg")
{
	m_DamageBlockManager.Initialize("Resources/Images/Level_1_Spikes.svg");
	m_CollectibleManager.Initliaze("Resources/Initializers/Collectibles.txt");
	m_CameraZoneManager.Initialize("Resources/Initializers/CameraZones.txt");
	m_RisingHandManager.Initialize("Resources/Initializers/RisingHands.txt");
	m_CrabEnemyManager.Initialize("Resources/Initializers/Crabs.txt");
	m_CannonEnemyManager.Initialize("Resources/Initializers/Cannons.txt");
	m_FallingSpikeManager.Initialize("Resources/Initializers/FallingSpikes.txt");
	m_CameraZoneManager.Initialize("Resources/Initializers/CameraZones.txt");
}

void Level_1::Reset()
{
	LevelBase::Reset();

	m_RisingHandManager.Reset();
	m_CrabEnemyManager.Reset();
	m_PlayerAvatar.Reset();
	m_CollectibleManager.Reset();
	m_Camera.Reset();
	m_FallingSpikeManager.Reset();
	m_CannonEnemyManager.Reset();
}

void Level_1::Draw(const GameState& currentGameState) const
{
	glPushMatrix();
		glScalef(m_ScaleFactor, m_ScaleFactor, 1);
		m_Camera.Transform();
		m_Lava.Draw();
		m_CannonEnemyManager.Draw();
		m_DamageBlockManager.Draw();
		m_RisingHandManager.Draw();
		m_CrabEnemyManager.Draw();
		m_CollectibleManager.Draw();
		m_FallingSpikeManager.Draw();
	glPopMatrix();

	LevelBase::Draw(currentGameState);

	glPushMatrix();
		glScalef(m_ScaleFactor, m_ScaleFactor, 1);
		m_Camera.Transform();
		m_DamageBlockManager.Draw();
	glPopMatrix();
}

void Level_1::Update(GameState& currentGameState, MenuManager& menuManager, ScoreManager& scoreManager)
{
	LevelBase::Update(currentGameState, menuManager, scoreManager);

	m_CollectibleManager.Update(m_PlayerAvatar, scoreManager);
	m_DamageBlockManager.Update(m_PlayerAvatar);
	m_RisingHandManager.Update(m_PlayerAvatar, m_PlayerAvatar.GetProjectileManager().GetProjectiles(), scoreManager);
	m_CrabEnemyManager.Update(m_PlayerAvatar, *this, m_PlayerAvatar.GetProjectileManager().GetProjectiles(), scoreManager);
	m_CannonEnemyManager.Update(m_PlayerAvatar, GetLevelVerts(), m_PlayerAvatar.GetProjectileManager().GetProjectiles(), scoreManager);
	m_FallingSpikeManager.Update(m_PlayerAvatar, GetLevelVerts());
	m_Lava.Update(m_PlayerAvatar);

	if (HasReachedEnd(m_PlayerAvatar.GetShape()) && currentGameState != GameState::Finished)
	{
		PlayerFinished(currentGameState, menuManager, scoreManager);
	};
}

void Level_1::PlayerFinished(GameState& currentGameState, MenuManager& menuManager, ScoreManager& scoreManager)
{
	LevelBase::PlayerFinished(currentGameState, menuManager, scoreManager);
	menuManager.OpenMenu(MenuType::Finished);
}
