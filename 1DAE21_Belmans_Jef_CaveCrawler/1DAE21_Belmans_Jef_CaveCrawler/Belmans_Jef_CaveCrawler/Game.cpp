#include "pch.h"
#include "Game.h"
#include "Enums.h"
#include "SoundManager.h"

Game::Game( const Window& window ) 
	: m_Window{ window }
	, m_HUD { window, 4 }
	, m_MenuManager { window.width, window.height }
	, m_DoQuit{ false }
	, m_CurrentGameState { GameState::MainMenu }
	, m_LevelManager { window }
	, m_ScoreManager { m_HUD }
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
	SoundManager::GetInstance()->PlayMainSoundtrack();
	ShowControls();
}

void Game::Cleanup( )
{
	delete Time::GetInstance();
	delete SoundManager::GetInstance();
}

void Game::Update( float elapsedSec )
{
	m_LevelManager.Update(m_MenuManager, m_CurrentGameState, m_ScoreManager);
}

void Game::Draw() const
{
	ClearBackground();

	m_LevelManager.Draw(m_CurrentGameState);
	m_HUD.Draw();
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
		ShowControls();
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
	case SDL_SCANCODE_ESCAPE:
		if (m_CurrentGameState == GameState::InGame)
		{
			Time::GetInstance()->m_TimeScale = 0.0f;
			m_CurrentGameState = GameState::Paused;
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

void Game::ShowControls() const
{
	std::cout << "Navigate the menu using the [UP] and [DOWN] key, press [ENTER] to select" <<
		"\r\nMove using the [A] and [D] Keys, jump with [SPACE] and shoot with [RCTRL]." <<
		"\r\nPress [ESC] to pause the game" << std::endl;
}

void Game::ResetLevel()
{
	m_LevelManager.Reset();
	SoundManager::GetInstance()->PlayMainSoundtrack();
	Time::GetInstance()->m_TimeScale = 1.0f;
	SetGameState(GameState::InGame);
}

void Game::SetGameState(const GameState& state)
{
	m_CurrentGameState = state;
}

void Game::BackToMainMenu()
{
	ResetScore();
	m_MenuManager.OpenMenu(MenuType::Main);
	SetGameState(GameState::MainMenu);
}

void Game::OpenOptionsMenu()
{
	m_MenuManager.OpenMenu(MenuType::Options);
	SetGameState(GameState::MainMenu);
}

void Game::ResetScore()
{
	m_ScoreManager.ResetScore();
}

void Game::LoadLevelByName(const std::string& levelName)
{
	m_LevelManager.LoadLevelByName(levelName);
	ResetLevel();
	HUD::UpdateHealth(4);
}

void Game::LoadNextLevel()
{
	m_LevelManager.LoadNextLevel();
	ResetLevel();
	HUD::UpdateHealth(4);
}
