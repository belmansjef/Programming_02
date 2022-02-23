#include <iostream>
#include "pch.h"
#include "Game.h"
#include "Enemy.h"
#include "Avatar.h"

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
	CreateEnemies();
	CreatePlayer();
}

void Game::Cleanup( )
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
	for (int i = 0; i < m_NrEnemies; i++)
	{
		delete m_pEnemies[i];
		m_pEnemies[i] = nullptr;
	}
}

void Game::Update( float elapsedSec )
{
	UpdatePlayer(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );

	DrawEnemies();
	DrawPlayer();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_pPlayer->ProcessKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{

}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		const Rectf mouseRect
		{
			float(e.x) - 25.0f,
			float(e.y) - 25.0f,
			50.0f,
			50.0f
		};

		//for (int i = 0; i < m_NrEnemies; i++)
		//{
		//	if (m_pEnemies[i]->DoHitTest(mouseRect))
		//	{
		//		delete m_pEnemies[i];
		//		m_pEnemies[i] = nullptr;
		//	}
		//}
		break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::CreateEnemies()
{
	// Fully customisable enemy instantiation
	const int enemiesPerRow{ 10 };
	const float enemySpacing{ 15.0f };
	const float enemySize{ (m_Window.width - (enemySpacing * (enemiesPerRow + 1))) / enemiesPerRow };

	for (int i = 0; i < m_NrEnemies; i++)
	{
		const Point2f enemyPos
		{
			(enemySpacing + ((enemySpacing + enemySize) * (i % enemiesPerRow))) + enemySize / 2.0f,
			(m_Window.height - ((enemySpacing + enemySize) * (i / enemiesPerRow + 1))) + enemySize / 2.0f
		};

		m_pEnemies[i] = new Enemy(enemyPos, enemySize, enemySize);
	}
}

void Game::DrawEnemies() const
{
	for (int i = 0; i < m_NrEnemies; i++)
	{
		m_pEnemies[i]->Draw();
	}
}

void Game::CreatePlayer()
{
	const float playerWidth{ 40.0f };
	const float playerHeight{ 40.0f };
	const float verticalSpacing{ 10.0f };

	const Point2f playerCenter
	{
		m_Window.width / 2.0f,
		playerHeight + verticalSpacing
	};

	const Rectf windowBoundaries
	{
		0.0f,
		0.0f,
		m_Window.width,
		m_Window.height
	};

	m_pPlayer = new Avatar(playerCenter, playerWidth, playerHeight, windowBoundaries);
}

void Game::DrawPlayer() const
{
	m_pPlayer->Draw();
}

void Game::UpdatePlayer(float elapsedSec) const
{
	m_pPlayer->Update(elapsedSec, *m_pEnemies, m_NrEnemies);
}
