#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	for (size_t i = 0; i < 32; i++)
	{
		const Point2f leftBottom{ 16.0f + (32.0f * i), 16.0f };
		m_CollectibleManager.AddItem(leftBottom, Collectible::Type(i % 2));
	}
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

	m_CollectibleManager.Draw();
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
