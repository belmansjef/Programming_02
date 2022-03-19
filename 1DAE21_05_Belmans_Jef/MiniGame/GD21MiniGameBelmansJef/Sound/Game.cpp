#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_StreamMenuText{ "Resources/Images/StreamsMenu.png" }
	,m_EffectMenuText { "Resources/Images/EffectsMenu.png" }
	,m_StreamTest {true}
	,m_DonkeySS { "Resources/Sounds/DonkeyKong.mp3"}
	,m_MarioSS { "Resources/Sounds/Mario.mp3"}
	,m_LaserSE { "Resources/Sounds/laser.ogg" }
	,m_JinglesSE { "Resources/Sounds/jingles.ogg" }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawMenu( );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_RIGHT:
	case SDLK_LEFT:
		SwitchTest( );
		break;
	default:
		// Handle user request
		if ( m_StreamTest )
		{
			TestStreams( e );
		}
		else
		{
			TestEffects( e );
		}
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

void Game::DrawMenu( ) const
{
	if ( m_StreamTest )
	{
		m_StreamMenuText.Draw( );
	}
	else
	{
		m_EffectMenuText.Draw( );
	}
}

void Game::SwitchTest( )
{
	if ( m_StreamTest )
	{
		m_DonkeySS.Stop();
		m_MarioSS.Stop();
	}
	else
	{
		m_LaserSE.StopAll();
		m_JinglesSE.StopAll();
	}
	m_StreamTest = !m_StreamTest;
}

void Game::TestStreams( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_1:
	case SDLK_KP_1:
		// Play Donkey Kong (repeated)
		m_DonkeySS.Play(true);
		break;
	case SDLK_2:
	case SDLK_KP_2:
		// Play Mario (not repeated)
		m_MarioSS.Play(false);
		break;
	case SDLK_p:
		// Pause the SoundStream
		m_DonkeySS.Pause();
		m_MarioSS.Pause();
		break;
	case SDLK_r:
		// Resume the SoundStream
		m_DonkeySS.Resume();
		m_MarioSS.Resume();
		break;
	case SDLK_s:
		// Stop the SoundStream
		m_DonkeySS.Stop();
		m_MarioSS.Stop();
		break;
	case SDLK_UP:
		// Increase volume of SoundStream
		m_DonkeySS.SetVolume(m_DonkeySS.GetVolume() + 1);
		m_MarioSS.SetVolume(m_MarioSS.GetVolume() + 1);
		break;
	case SDLK_DOWN:
		// Decrease volume of SoundStream
		m_DonkeySS.SetVolume(m_DonkeySS.GetVolume() - 1);
		m_MarioSS.SetVolume(m_MarioSS.GetVolume() - 1);
		break;
	}
}

void Game::TestEffects( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_1:
	case SDLK_KP_1:
		// Play laser (repeated)
		m_LaserSE.Play(50000);
		break;
	case SDLK_2:
	case SDLK_KP_2:
		// Play jingles (a number of times)
		m_JinglesSE.Play(5);
		break;
	case SDLK_p:
		// Pause all soundEffects
		m_LaserSE.PauseAll();
		m_JinglesSE.PauseAll();
		break;
	case SDLK_r:
		// Resume all soundEffects
		m_LaserSE.ResumeAll();
		m_JinglesSE.ResumeAll();
		break;
	case SDLK_s:
		// Stop  all soundEffects
		m_LaserSE.StopAll();
		m_JinglesSE.StopAll();
		break;
	case SDLK_UP:
		// Increase volume of all SoundEffects
		m_LaserSE.SetVolume(m_LaserSE.GetVolume() + 1);
		m_JinglesSE.SetVolume(m_JinglesSE.GetVolume() + 1);
		break;
	case SDLK_DOWN:
		// Decrease volume of all SoundEffects
		m_LaserSE.SetVolume(m_LaserSE.GetVolume() - 1);
		m_JinglesSE.SetVolume(m_JinglesSE.GetVolume() - 1);
		break;
	}
}

