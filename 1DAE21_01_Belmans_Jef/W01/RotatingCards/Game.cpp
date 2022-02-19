#include "pch.h"
#include "Game.h"
#include "Card.h"
#include "Texture.h"

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
	const Texture* pCardTexture = new Texture("Resources/101.png");
	const float cardWidth{ pCardTexture->GetWidth() };
	cout << cardWidth;
	delete pCardTexture;
	pCardTexture = nullptr;

	float windowBound{};
	if (m_Window.width > m_Window.height)
	{
		windowBound = m_Window.height;
	}
	else if (m_Window.width < m_Window.height)
	{
		windowBound = m_Window.width;
	}

	const Circlef movementPath
	{
		m_Window.width / 2.0f,
		m_Window.height / 2.0f,
		(m_Window.height / 4.0f) - (cardWidth / 2.0f)
	};

	for (int i = 1; i <= 13; i++)
	{
		m_Cards.push_back(new Card(Card::Suit::hearts, i, (360.0f / 13.0f) * i, movementPath));
	}
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	for (int i = 0; i < m_Cards.size(); i++)
	{
		m_Cards[i]->Update(elapsedSec);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (int i = 0; i < m_Cards.size(); i++)
	{
		m_Cards[i]->Draw();
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
