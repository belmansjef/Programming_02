#include "pch.h"
#include "Game.h"
#include "Diamond.h"

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
	InitDiamonds(10);
}

void Game::Cleanup( )
{
	DeleteDiamonds();
}

void Game::Update( float elapsedSec )
{
	UpdateDiamonds(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground();

	DrawDiamonds();
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
	const Point2f mousePos{ float(e.x), float(e.y) };

	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		for (Diamond* dia : m_pDiamonds)
		{
			dia->CheckIfClicked(mousePos);
		}
		break;
	}
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
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitDiamonds(int nrDiamonds)
{
	for (size_t i = 0; i < nrDiamonds; i++)
	{
		const Point2f startPos
		{
			float(rand() % int(m_Window.width - 48)),
			float(rand() % int(m_Window.height - 48))
		};

		m_pDiamonds.push_back(new Diamond(startPos));
	}
}

void Game::DeleteDiamonds()
{
	for (Diamond* dia : m_pDiamonds)
	{
		delete dia;
		dia = nullptr;
	}
}

void Game::DrawDiamonds() const
{
	for (Diamond* dia : m_pDiamonds)
	{
		dia->Draw();
	}
}

void Game::UpdateDiamonds(float elapsedSec) const
{
	for (Diamond* dia : m_pDiamonds)
	{
		dia->Update(elapsedSec);
	}
}
