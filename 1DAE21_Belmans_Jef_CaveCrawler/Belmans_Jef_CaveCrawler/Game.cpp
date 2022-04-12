#include <iomanip>
#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_Camera{ window.width / m_ScaleFactor, window.height / m_ScaleFactor }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	// Load damagablocks
	m_DamageBlockManager.AddItemsFromSvgFile("Resources/Images/Level_1_Spikes.svg");

	// Load camerazones
	m_CameraZoneManager.AddItem(0.0f, 0.0f, 39.0f * 8.0f, 18.0f * 8.0f);
	m_CameraZoneManager.AddItem(39.0f * 8.0f, 0.0f, 34.0f * 8.0f, 18.0f * 8.0f);
	m_CameraZoneManager.AddItem(73.0f * 8.0f, 0.0f, 32.0f * 8.0f, 27.0f * 8.0f);
	m_CameraZoneManager.AddItem(0.0f, 18.0f * 8.0f, 73.0f * 8.0f, 18.0f * 8.0f);

	// Load risinghands
	m_RisingHandManager.AddItem(Point2f(128.0f, 24.0f), 3);
}

void Game::Cleanup( )
{

}

void Game::Update( float elapsedSec )
{
	// Lock framerate
	if (1000.0f / m_MaxFPS > (Time::deltaTime * 1000.0f))
	{
		m_FrameDelay = Uint32((1000.0f / m_MaxFPS - (Time::deltaTime * 1000.0f)));
	}
	SDL_Delay(m_FrameDelay);

	// Updates
	m_PlayerAvatar.Update(m_Level);
	m_Camera.UpdatePosition(m_PlayerAvatar.GetShape(), m_PlayerAvatar.ShouldTrack());
	m_Camera.SetLevelBoundaries(m_CameraZoneManager.GetCurrentZone(m_PlayerAvatar.GetShape()));

	m_DamageBlockManager.Update(m_PlayerAvatar.GetShape(), m_PlayerAvatar.GetHealth(), m_Camera);
	m_RisingHandManager.Update(m_PlayerAvatar.GetShape(), m_PlayerAvatar.GetHealth(), m_Camera, m_PlayerAvatar.GetProjectileManager().GetProjectiles());

	UpdateFrameStats();
}

void Game::Draw( ) const
{
	ClearBackground( );

	glPushMatrix();
		glScalef(m_ScaleFactor, m_ScaleFactor, 1);
		m_Camera.Transform();
		m_Level.DrawBackground();
		m_PlayerAvatar.Draw();
		m_DamageBlockManager.Draw();
		m_RisingHandManager.Draw();
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	m_PlayerAvatar.OnMouseDownEvent(e);
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::UpdateFrameStats()
{
	m_Frames++;
	m_FrameTime += Time::deltaTime + m_FrameDelay / 1000.0f;

	if (m_FrameTime > 1.0f) // Every second
	{
		m_FrameRate = float(m_Frames) * 0.5f + m_FrameRate * 0.5f; // Stabilize reading
		m_Frames = 0;
	
		m_AvgFrameTime = (1.0f / m_FrameRate) * 1000.0f;

		if (m_ShouldPrintStats)
		{
			std::cout << std::setprecision(2) << "[Frametime]\t\t[FPS]\r\n\t" << m_AvgFrameTime << " ms\t\t" << std::setprecision(3) << m_FrameRate << std::endl;
		}

		m_FrameTime = 0.0f;
	}
}
