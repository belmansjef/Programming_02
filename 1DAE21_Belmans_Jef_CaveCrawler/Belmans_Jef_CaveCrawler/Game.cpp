#include <iomanip>
#include "pch.h"
#include "Game.h"
#include "SoundManager.h"

Game::Game( const Window& window ) 
	: m_Window{ window }
	, m_Camera{ window.width / m_ScaleFactor, window.height / m_ScaleFactor }
	, m_EndScreenOverlay{ Rectf(0.0f, 0.0f, window.width, window.height) }
	, m_HUD { window, m_PlayerAvatar.GetHealth().GetCurrentHealth() }
	, m_MenuManager { window.width, window.height }
	, m_Cannon { Point2f(144.0f, 120.0f), 0.0f }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	SoundManager::GetInstance()->Initialize();

	// Load collectibles
	m_CollectibleManager.AddItem(Point2f(192.0f, 42.0f), Collectible::CollectibleType::points);
	m_CollectibleManager.AddItem(Point2f(192.0f, 50.0f), Collectible::CollectibleType::points);

	m_CollectibleManager.AddItem(Point2f(444.0f, 42.0f), Collectible::CollectibleType::points);
	m_CollectibleManager.AddItem(Point2f(444.0f, 50.0f), Collectible::CollectibleType::points);

	m_CollectibleManager.AddItem(Point2f(672.0f, 88.0f), Collectible::CollectibleType::points);
	m_CollectibleManager.AddItem(Point2f(672.0f, 96.0f), Collectible::CollectibleType::points);

	m_CollectibleManager.AddItem(Point2f(752.0f, 80.0f), Collectible::CollectibleType::points);
	m_CollectibleManager.AddItem(Point2f(752.0f, 88.0f), Collectible::CollectibleType::points);

	m_CollectibleManager.AddItem(Point2f(256.0f, 200.0f), Collectible::CollectibleType::points);
	m_CollectibleManager.AddItem(Point2f(272.0f, 200.0f), Collectible::CollectibleType::points);
	m_CollectibleManager.AddItem(Point2f(288.0f, 200.0f), Collectible::CollectibleType::points);
	m_CollectibleManager.AddItem(Point2f(304.0f, 200.0f), Collectible::CollectibleType::points);

	m_CollectibleManager.AddItem(Point2f(452.0f, 172.0f), Collectible::CollectibleType::points);
	m_CollectibleManager.AddItem(Point2f(452.0f, 180.0f), Collectible::CollectibleType::points);

	m_CollectibleManager.AddItem(Point2f(148.0f, 216.0f), Collectible::CollectibleType::health);

	// Load damagablocks
	m_DamageBlockManager.AddItemsFromSvgFile("Resources/Images/Level_1_Spikes.svg");

	// Load camerazones
	m_CameraZoneManager.AddItem(0.0f, 0.0f, 39.0f * 8.0f, 18.0f * 8.0f);
	m_CameraZoneManager.AddItem(39.0f * 8.0f, 0.0f, 34.0f * 8.0f, 18.0f * 8.0f);
	m_CameraZoneManager.AddItem(73.0f * 8.0f, 0.0f, 32.0f * 8.0f, 27.0f * 8.0f);
	m_CameraZoneManager.AddItem(0.0f, 18.0f * 8.0f, 73.0f * 8.0f, 18.0f * 8.0f);

	// Load risinghands
	m_RisingHandManager.AddItem(Point2f(192.0f, 24.0f), 3);
	m_RisingHandManager.AddItem(Point2f(128.0f, 208.0f), 3);

	// Load crabs
	m_CrabEnemyManager.AddItem(Point2f(704.0f, 24.0f), 1, 3);

	// Load Falling spikes
	m_FallingSpikeManager.AddItem(Point2f(128.0f, 120.0f));
	m_FallingSpikeManager.AddItem(Point2f(400.0f, 264.0f));
	m_FallingSpikeManager.AddItem(Point2f(444.0f, 120.0f));
}

void Game::Cleanup( )
{
	SoundManager::GetInstance()->Destroy();
	std::cout << "Game destuctor" << std::endl;
}

void Game::Update( float elapsedSec )
{
	// Lock framerate
	m_FrameDelay = UINT32(m_MaxFrameTime - (Time::deltaTime));
	SDL_Delay(m_FrameDelay);

	// Updates
	if (m_CurrentGameState != GameState::Dead)
	{
		m_PlayerAvatar.Update(m_Level, m_CurrentGameState);
		m_Camera.UpdatePosition(m_PlayerAvatar.GetShape(), m_PlayerAvatar.ShouldTrack());
		m_Camera.SetCameraBounds(m_CameraZoneManager.GetCurrentZone(m_PlayerAvatar.GetShape()));
	}

	// Managers
	m_DamageBlockManager.Update(m_PlayerAvatar.GetShape(), m_PlayerAvatar.GetHealth());
	m_RisingHandManager.Update(m_PlayerAvatar.GetShape(), m_PlayerAvatar.GetProjectileManager().GetProjectiles(), m_PlayerAvatar.GetHealth());
	m_CrabEnemyManager.Update(m_PlayerAvatar.GetShape(), m_Level, m_PlayerAvatar.GetProjectileManager().GetProjectiles(), m_PlayerAvatar.GetHealth());
	m_CollectibleManager.Update(m_PlayerAvatar.GetShape(), m_PlayerAvatar.GetHealth());
	m_Lava.Update(m_PlayerAvatar.GetShape(), m_PlayerAvatar.GetHealth());
	m_FallingSpikeManager.Update(m_PlayerAvatar.GetShape(), m_Level.GetLevelVerts(), m_PlayerAvatar.GetHealth());

	m_Cannon.Update(m_PlayerAvatar.GetShape(), m_PlayerAvatar.GetHealth(), m_Level.GetLevelVerts());

	if (m_PlayerAvatar.GetIsDead() && m_CurrentGameState != GameState::Dead)
	{
		PlayerDied();
	}

	if (m_Level.HasReachedEnd(m_PlayerAvatar.GetShape()) && m_CurrentGameState != GameState::Finished)
	{
		PlayerFinished();
	};
	
	UpdateFrameStats();
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
		m_Cannon.Draw();
		m_DamageBlockManager.Draw();
		m_RisingHandManager.Draw();
		m_CrabEnemyManager.Draw();
		m_CollectibleManager.Draw();
		m_Lava.Draw();
		m_FallingSpikeManager.Draw();
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
			Time::SetTimeScale(0.0f);
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
	Time::SetTimeScale(0.0f);
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

	Time::SetTimeScale(1.0f);
	SetGameState(GameState::InGame);
}

void Game::UpdateFrameStats()
{
	m_FrameRate++;
	m_FrameTime += Time::deltaTime;

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
