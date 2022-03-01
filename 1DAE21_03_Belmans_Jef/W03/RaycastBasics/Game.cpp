#include "pch.h"
#include "Game.h"
#include "utils.h"

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
	DrawSurface();
	CastRay(m_Surface, m_RayP1, m_MousePos);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{

}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
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
	glClearColor( 0.4f, 0.4f, 0.4f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DrawSurface() const
{
	utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
	utils::FillPolygon(m_Surface);

	utils::SetColor(Color4f(1.0f, 0.5f, 0.2f, 1.0f));
	utils::DrawPolygon(m_Surface);
}

void Game::CastRay(const std::vector<Point2f>& surface, const Point2f& start, const Point2f& end) const
{
	DrawRay();
	utils::HitInfo hitInfo{};

	if (utils::Raycast(surface, start, end, hitInfo))
	{
		// Hit circle
		utils::SetColor(Color4f(1.0f, 1.0f, 0.0f, 1.0f));
		utils::FillEllipse(hitInfo.intersectPoint, 5.0f, 5.0f);

		// Draw inner and outer ray
		const Vector2f innerRay(m_RayP1, hitInfo.intersectPoint);
		const Vector2f outerRay(hitInfo.intersectPoint, m_MousePos);

		utils::SetColor(Color4f(0.2f, 0.2f, 1.0f, 1.0f));
		DrawVector(innerRay, m_RayP1);

		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
		DrawVector(outerRay, hitInfo.intersectPoint);

		// Normal
		utils::SetColor(Color4f(0.0f, 1.0f, 0.0f, 1.0f));
		DrawVector(-hitInfo.normal * 30.0f, hitInfo.intersectPoint);
		
		// Reflection
		const Vector2f rayVector{ m_RayP1, m_MousePos };
		const Vector2f reflectionVector{ rayVector.Reflect(hitInfo.normal) };

		utils::SetColor(Color4f(0.0f, 0.0f, 1.0f, 1.0f));
		DrawVector(reflectionVector * (1 - hitInfo.lambda), hitInfo.intersectPoint);
	}
}

void Game::DrawRay() const
{
	utils::SetColor(Color4f(1.0f, 1.0f, 0.0f, 1.0f));
	utils::DrawLine(m_RayP1, m_MousePos);
}

void Game::DrawVector(const Vector2f& v, const Point2f& startPoint) const
{
	Point2f endPoint{ startPoint + v };
	utils::DrawLine(startPoint, endPoint, 2.0f);
}
