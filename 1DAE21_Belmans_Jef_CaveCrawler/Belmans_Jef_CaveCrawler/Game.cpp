#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_Camera{ window.width, window.height }
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
	m_PlayerAvater.Update(elapsedSec, m_Level);
}

void Game::Draw( ) const
{
	ClearBackground( );

	glPushMatrix();
		m_Camera.Transform(m_PlayerAvater.GetShape());
		m_Level.DrawBackground();
		m_PlayerAvater.Draw();
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
