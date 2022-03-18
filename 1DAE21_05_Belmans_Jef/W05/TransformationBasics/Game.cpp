#include "pch.h"
#include <iostream>
#include "Game.h"
#include "Texture.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_pTexture{ new Texture("Resources/Images/Diamond.png") }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	std::cout << "a: rotate ccw\r\nd: rotate cw\r\nw: zoom in\\r\ns: zoom out\r\nArrows: translate";
}

void Game::Cleanup( )
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Game::Update( float elapsedSec )
{
	GetInput(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );

	DrawDiamond();
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
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		if (utils::IsPointInPolygon(Point2f(float(e.x), float(e.y)), m_TransVertices, 4))
		{
			m_IsSelected = !m_IsSelected;
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

void Game::DrawDiamond() const
{
	if (m_IsSelected)
	{
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		utils::SetColor(Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	}
	
	utils::DrawPolygon(m_TransVertices, 4, true, 2.0f);

	glPushMatrix();
	glTranslatef(m_Translation.x, m_Translation.y, 0);
	glRotatef(m_Rotation, 0, 0, 1);
	glScalef(m_Scaling, m_Scaling, 1);
	m_pTexture->Draw();
	glPopMatrix();
}

void Game::GetInput(float elapsedSec)
{
	const Uint8* pKeyStates = SDL_GetKeyboardState(nullptr);
	
	m_Rotation += (60 * elapsedSec) * (pKeyStates[SDL_SCANCODE_A] - pKeyStates[SDL_SCANCODE_D]);

	m_Scaling *= 1 + 3 * elapsedSec * pKeyStates[SDL_SCANCODE_W];
	m_Scaling /= 1 + 3 * elapsedSec * pKeyStates[SDL_SCANCODE_S];

	m_Translation.x += 120 * elapsedSec * (pKeyStates[SDL_SCANCODE_RIGHT] - pKeyStates[SDL_SCANCODE_LEFT]);
	m_Translation.y += 120 * elapsedSec * (pKeyStates[SDL_SCANCODE_UP] - pKeyStates[SDL_SCANCODE_DOWN]);
	
	Matrix2x3 matTranslate, matRotate, matScale;
	matTranslate.SetAsTranslate(m_Translation);
	matRotate.SetAsRotate(m_Rotation);
	matScale.SetAsScale(m_Scaling);

	Matrix2x3 matWorld{ matTranslate * matRotate * matScale };
	matWorld.Transform(m_Vertices, m_TransVertices, 4);
}
