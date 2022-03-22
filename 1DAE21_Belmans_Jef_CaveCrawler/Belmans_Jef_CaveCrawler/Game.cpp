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
	m_Camera.SetLevelBoundaries(m_Level.GetBoundaries());
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
	m_Camera.UpdatePosition(m_PlayerAvatar.GetShape(), m_PlayerAvatar.ShouldTrack());
	m_PlayerAvatar.Update(m_Level);
	UpdateFrameStats(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );

	glPushMatrix();
		glScalef(m_ScaleFactor, m_ScaleFactor, 1);
		m_Camera.Transform();
		m_Level.DrawBackground();
		m_PlayerAvatar.Draw();
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
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::UpdateFrameStats(float elapsedSec)
{
	m_Frames++;
	m_FrameTime += elapsedSec + m_FrameDelay / 1000.0f;

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
