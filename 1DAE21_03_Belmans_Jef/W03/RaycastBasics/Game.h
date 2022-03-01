#pragma once
#include "utils.h"

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;
	const std::vector<Point2f> m_Surface
	{
		Point2f(50.0f, 50.0f),
		Point2f(m_Window.width / 2.0f, 25.0f),
		Point2f(m_Window.width - 50.0f, 50.0f),
		Point2f(m_Window.width - 50.0f, m_Window.height - 100.0f),
		Point2f(m_Window.width / 2.0f, m_Window.height - 25.0f),
		Point2f(50.0f, m_Window.height - 100.0f)
	};

	const Point2f m_RayP1{ m_Window.width / 2.0f, m_Window.height / 2.0f };
	Point2f m_MousePos{};

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void DrawSurface( ) const;
	void CastRay(const std::vector<Point2f>& surface, const Point2f& start, const Point2f& end) const;
	void DrawRay( ) const;
	void DrawVector(const Vector2f& v, const Point2f& startPoint) const;
};