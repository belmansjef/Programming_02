#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	: m_Window{ window }
	, m_MousePos{ Point2f() }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	
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

	// Surface (orange)
	Point2f surfaceP1{ 350.0f, 50.0f };
	Point2f surfaceP2{ 150.0f, 250.0f };
	utils::SetColor(Color4f(1.0f, 0.5f, 0.2f, 1.0f));
	utils::DrawLine(surfaceP1, surfaceP2, 4.0f);

	// Draw Ray (yellow)
	Point2f rayP1{ 100.0f, 40.0f };
	// Point2f rayP2{ 350.0f, 150.0f };
	utils::SetColor(Color4f(1.0f, 1.0f, 0.0f, 1.0f));
	utils::DrawLine(rayP1, m_MousePos, 2.0f);

	// Raycast
	utils::HitInfo hitInfo{};
	std::vector<Point2f> surface{ surfaceP1, surfaceP2 };

	if (utils::Raycast(surface, rayP1, m_MousePos, hitInfo))
	{
		// Intersection Point
		utils::SetColor(Color4f(1.0f, 1.0f, 0.0f, 1.0f));
		utils::FillEllipse(hitInfo.intersectPoint, 4.0f, 4.0f);

		// Normal
		utils::SetColor(Color4f(0.0f, 1.0f, 0.0f, 1.0f));
		DrawVector(hitInfo.normal * 100.0f, hitInfo.intersectPoint);

		// Lambda
		std::cout << "Distance between hit and end point: " << hitInfo.lambda << std::endl;

		// Reflection vector
		utils::SetColor(Color4f(10.0f, 1.0f, 1.0f, 1.0f));
		Vector2f rayVector{ rayP1, m_MousePos };
		Vector2f reflectedVector{ rayVector.Reflect(hitInfo.normal) };

		DrawVector(reflectedVector * (1 - hitInfo.lambda), hitInfo.intersectPoint);
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{

}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_MousePos.x = float(e.x);
	m_MousePos.y = float(e.y);
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DrawVector(const Vector2f& v, const Point2f& startPoint) const
{
	Point2f endPoint{ startPoint + v };

	utils::DrawLine(startPoint, endPoint, 2.0f);
}
