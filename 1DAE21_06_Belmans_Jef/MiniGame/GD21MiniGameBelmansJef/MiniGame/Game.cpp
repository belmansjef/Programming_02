#include <iostream>
#include "pch.h"
#include "Game.h"

Game::Game( const Window& window )
	: m_Window{ window }
	, m_Camera{ window.width, window.height }
	, m_EndScreenOverlay{ 0.0f, 0.0f, window.width, window.height }
	, m_Hud{ Point2f(10.0f, window.height - 50.0f), 0 }
{	 
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	ShowTestMessage( );
	AddPowerUps( );
	m_Camera.SetLevelBoundaries(m_Level.GetBoundaries());
	m_EndReached = false;
	m_Hud.SetTotalPowerUps(int(m_PowerUpManager.Size()));
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	if (m_EndReached) return;

	// Update game objects
	m_PowerUpManager.Update( elapsedSec );
	m_Avatar.Update( elapsedSec, m_Level );

	// Do collision
	DoCollisionTests( );

	m_EndReached = m_Level.HasReachedEnd(m_Avatar.GetShape());
}

void Game::Draw( ) const
{
	ClearBackground( );

	glPushMatrix();
		m_Camera.Transform(m_Avatar.GetShape());
		m_Level.DrawBackground( );
		m_PowerUpManager.Draw( );
		m_Avatar.Draw( );
		m_Level.DrawForeground( );
	glPopMatrix();

	m_Hud.Draw();

	if (m_EndReached)
	{
		utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 0.8f));
		utils::FillRect(m_EndScreenOverlay);
	}
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


void Game::ShowTestMessage( ) const
{
	std::cout << "--> Avatar test <--\n";
	std::cout << "Verify that the avatar behaves as follows.\n";
	std::cout << "- Moves along the level when the left/right arrow is pressed.\n";
	std::cout << "- Doesn't move when it is on the ground and no key is pressed.\n";
	std::cout << "- Jumps only when it is on the ground and the up arrow key is pressed.\n";
	std::cout << "- Doesn't move during 1 second when hitting a power up.\n";
	std::cout << "- Starts moving again ( e.g. falling ) after this second.\n";
	std::cout << "- The number of small rectangles in the bottom left corner is equal to the number of hit power ups.\n";
	std::cout << "- Has a red color when it is moving.\n";
	std::cout << "- Has a yellow color when it is waiting.\n";
	std::cout << "- Has a blue color when it is transforming.\n";

}

void Game::AddPowerUps( )
{
	m_PowerUpManager.AddItem( Point2f{ 185.0f, 500 - 183.0f }, PowerUp::Type::brown );
	m_PowerUpManager.AddItem( Point2f{ 435.0f, 500 - 133.0f }, PowerUp::Type::green );
	m_PowerUpManager.AddItem( Point2f{ 685.0f, 500 - 183.0f }, PowerUp::Type::brown );
}

void Game::DoCollisionTests( )
{
	if ( m_PowerUpManager.HitItem( m_Avatar.GetShape( ) ) )
	{
		m_Avatar.PowerUpHit( );
		m_Hud.PowerUpHit();
	}
}

