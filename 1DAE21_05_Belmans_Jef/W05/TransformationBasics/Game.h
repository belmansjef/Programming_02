#pragma once
#include "utils.h"
#include "Matrix2x3.h"

class Texture;
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

	Texture* m_pTexture{};

	const Point2f m_Vertices[4]
		{ Point2f(24.0f, 48.0f)
		, Point2f(48.0f, 24.0f)
		, Point2f(24.0f, 0.0f)
		, Point2f(0.0f, 24.0f)};

	float m_Rotation{ 0.0f };
	float m_Scaling{ 1.0f };
	Vector2f m_Translation{ 0.0f, 0.0f };

	Point2f m_TransVertices[4]
		{ m_Vertices[0]
		, m_Vertices[1]
		, m_Vertices[2]
		, m_Vertices[3]};

	bool m_IsSelected{};

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void DrawDiamond() const;
	void GetInput(float elapsedSec);
};