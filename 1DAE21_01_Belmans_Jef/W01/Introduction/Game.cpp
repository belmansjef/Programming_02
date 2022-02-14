#include "pch.h"
#include "Game.h"
#include "Ball.h"
#include "Texture.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_pLogo{new Texture("Resources/DAE.png")}
	,m_pText{ new Texture("Hello World!", "Resources/Gameplay.ttf", 24, Color4f(1.0f, 1.0f, 0.0f, 1.0f)) }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	for (int i = 0; i < m_BallSize; i++)
	{
		m_pBalls[i] = new Ball(Point2f(float(rand() % 300 + 20), 100.0f), Vector2f(80.0f, 80.0f), Color4f(0.0f, 1.0f, 0.0f, 1.0f), 50.0f);
	}
}

void Game::Cleanup( )
{
	for (int i = 0; i < m_BallSize; i++)
	{
		delete m_pBalls[i];
		m_pBalls[i] = nullptr;
	}

	delete m_pText;
	m_pText = nullptr;

	delete m_pLogo;
	m_pLogo = nullptr;
}

void Game::Update( float elapsedSec )
{
	for (int i = 0; i < m_BallSize; i++)
	{
		m_pBalls[i]->Update(elapsedSec,Rectf(0.0f, 0.0f, m_Window.width, m_Window.height));
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (int i = 0; i < m_BallSize; i++)
	{
		m_pBalls[i]->Draw();
	}

	for (int i = 0; i < 3; i++)
	{
		m_pLogo->Draw(Point2f((m_pLogo->GetWidth() + 20.0f) * i + 20.0f, m_Window.height / 2.0f - m_pLogo->GetHeight() / 2.0f));
		m_pText->Draw(Point2f((m_pLogo->GetWidth() + 20.0f) * i + 20.0f, m_Window.height / 2.0f - m_pLogo->GetHeight() / 2.0f - m_pText->GetHeight()));
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
