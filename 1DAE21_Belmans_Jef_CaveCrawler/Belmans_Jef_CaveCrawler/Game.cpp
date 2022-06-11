#include <iomanip>
#include "pch.h"
#include "Game.h"
#include "SoundManager.h"
#include "Enums.h"

Game::Game( const Window& window ) 
	: m_Window{ window }
	, m_Camera{ window.width / m_ScaleFactor, window.height / m_ScaleFactor }
	, m_EndScreenOverlay{ Rectf(0.0f, 0.0f, window.width, window.height) }
	, m_HUD { window, m_PlayerAvatar.GetHealth().GetCurrentHealth() }
	, m_MenuManager { window.width, window.height }
	, m_DoQuit{ false }
	, m_CurrentGameState { GameState::MainMenu }
	, m_BossManager { 128.0f, 24.0f }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	SoundManager::GetInstance()->Initialize("Resources/Initializers/Sounds.txt");
	m_DamageBlockManager.Initialize("Resources/Images/Level_1_Spikes.svg");
	m_CollectibleManager.Initliaze("Resources/Initializers/Collectibles.txt");
	m_CameraZoneManager.Initialize("Resources/Initializers/CameraZones.txt");
	m_RisingHandManager.Initialize("Resources/Initializers/RisingHands.txt");
	m_CrabEnemyManager.Initialize("Resources/Initializers/Crabs.txt");
	m_CannonEnemyManager.Initialize("Resources/Initializers/Cannons.txt");
	m_FallingSpikeManager.Initialize("Resources/Initializers/FallingSpikes.txt");
}

void Game::Cleanup( )
{
	delete Time::GetInstance();
	delete SoundManager::GetInstance();
	std::cout << "Game destuctor" << std::endl;
}

void Game::Update( float elapsedSec )
{
	// Lock framerate
	m_FrameDelay = UINT32(m_MaxFrameTime - (Time::GetInstance()->m_DeltaTime));
	SDL_Delay(m_FrameDelay);

	// Updates
	m_PlayerAvatar.Update(m_Level, m_CurrentGameState);
	if (m_CurrentGameState != GameState::Dead)
	{
		m_Camera.UpdatePosition(m_PlayerAvatar.GetShape(), m_PlayerAvatar.ShouldTrack());
		m_Camera.SetCameraBounds(m_CameraZoneManager.GetCurrentZone(m_PlayerAvatar.GetShape()));
	}

	// Managers
	m_DamageBlockManager.Update(m_PlayerAvatar);
	m_RisingHandManager.Update(m_PlayerAvatar, m_PlayerAvatar.GetProjectileManager().GetProjectiles());
	m_CrabEnemyManager.Update(m_PlayerAvatar, m_Level, m_PlayerAvatar.GetProjectileManager().GetProjectiles());
	m_CollectibleManager.Update(m_PlayerAvatar);
	m_Lava.Update(m_PlayerAvatar);
	m_FallingSpikeManager.Update(m_PlayerAvatar, m_Level.GetLevelVerts());
	m_CannonEnemyManager.Update(m_PlayerAvatar, m_Level.GetLevelVerts(), m_PlayerAvatar.GetProjectileManager().GetProjectiles());
	m_BossManager.Update(m_PlayerAvatar, m_Level);

	if (m_PlayerAvatar.GetIsDead() && m_CurrentGameState != GameState::Dead)
	{
		PlayerDied();
	}

	if (m_Level.HasReachedEnd(m_PlayerAvatar.GetShape()) && m_CurrentGameState != GameState::Finished)
	{
		PlayerFinished();
	};
	
	// UpdateFrameStats();
}

void Game::Draw() const
{
	ClearBackground();

	glPushMatrix();
		glScalef(m_ScaleFactor, m_ScaleFactor, 1);
		m_Camera.Transform();
		m_Level.DrawLevel();
		m_PlayerAvatar.Draw();

		// Managers
		m_CannonEnemyManager.Draw();
		m_DamageBlockManager.Draw();
		m_RisingHandManager.Draw();
		m_CrabEnemyManager.Draw();
		m_CollectibleManager.Draw();
		m_Lava.Draw();
		m_FallingSpikeManager.Draw();
		m_BossManager.Draw();
	glPopMatrix();

	// Draw HUD and overlays after popping world view
	switch (m_CurrentGameState)
	{
	case GameState::InGame:
		m_HUD.Draw();
		break;
	case GameState::Finished:
		utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 0.75f));
		utils::FillRect(m_EndScreenOverlay);
		break;
	}

	m_MenuManager.DrawActiveMenu();
}


void Game::SetDoQuit(bool shouldQuit)
{
	m_DoQuit = shouldQuit;
}

bool Game::GetDoQuit() const
{
	return m_DoQuit;
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.scancode)
	{
	case SDL_SCANCODE_I:
		std::cout << "Move using the [WASD] Keys, jump with [SPACE] and shoot with [RCTRL]." <<
			"\r\nPress [PgUp] and [PgDn] to control the volume\r\nPress [R] to reset the level\r\nPress [ESC] to pause the game" << std::endl;
		break;
	case SDL_SCANCODE_R:
		ResetLevel();
		break;
	case SDL_SCANCODE_UP:
		m_MenuManager.CycleSelection(true);
		break;
	case SDL_SCANCODE_DOWN:
		m_MenuManager.CycleSelection(false);
		break;
	case SDL_SCANCODE_RETURN:
		m_MenuManager.Enter(*this);
		break;
	case SDL_SCANCODE_PAGEUP:
		SoundManager::GetInstance()->AdjustVolume(20.0f);
		break;
	case SDL_SCANCODE_PAGEDOWN:
		SoundManager::GetInstance()->AdjustVolume(-20.0f);
		break;
	case SDL_SCANCODE_ESCAPE:
		if (m_CurrentGameState == GameState::InGame)
		{
			Time::GetInstance()->m_TimeScale = 0.0f;
			m_MenuManager.OpenMenu(MenuType::Pause);
		}
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::PlayerDied()
{
	SetGameState(GameState::Dead);
	m_MenuManager.OpenMenu(MenuType::GameOver);
}

void Game::PlayerFinished()
{
	Time::GetInstance()->m_TimeScale = 0.0f;
	SetGameState(GameState::Finished);
	m_MenuManager.OpenMenu(MenuType::Finished); 

	SoundManager::GetInstance()->PlaySound(SoundType::levelFinish);
}

void Game::ResetLevel()
{
	m_RisingHandManager.Reset();
	m_CrabEnemyManager.Reset();
	m_PlayerAvatar.Reset();
	m_CollectibleManager.Reset();
	m_Camera.Reset();
	m_FallingSpikeManager.Reset();
	m_CannonEnemyManager.Reset();
	m_BossManager.Reset();

	Time::GetInstance()->m_TimeScale = 1.0f;
	SetGameState(GameState::InGame);
}

void Game::UpdateFrameStats()
{
	m_FrameRate++;
	m_FrameTime += Time::GetInstance()->m_DeltaTime;

	if (m_FrameTime >= 1.0f) // Every second
	{
		m_AvgFrameTime = 1000 / m_FrameRate;

		if (m_ShouldPrintStats)
		{
			std::cout << std::setprecision(2) << "[Frametime]\t\t[FPS]\r\n\t" << m_AvgFrameTime << " ms\t\t" << std::setprecision(3) << m_FrameRate << std::endl;
		}

		m_FrameTime = 0.0f;
		m_FrameRate = 0.0f;
	}
}

void Game::SetGameState(const GameState& state)
{
	m_CurrentGameState = state;
}

void Game::BackToMainMenu()
{
	m_MenuManager.OpenMenu(MenuType::Main);
	SetGameState(GameState::MainMenu);
}

void Game::OpenOptionsMenu()
{
	m_MenuManager.OpenMenu(MenuType::Options);
	SetGameState(GameState::MainMenu);
}
