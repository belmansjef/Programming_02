#pragma once
#include "Level.h"
#include "Avatar.h"
#include "Camera.h"
#include "CollectibleManager.h"

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
	const float m_ScaleFactor{ 6 };

	bool m_ShouldPrintStats{ false };
	int m_Frames{ 0 };
	float m_FrameTime{ 0.0f };
	float m_AvgFrameTime{ 0.0f };
	float m_FrameRate{ 0.0f };
	const float m_MaxFPS{ 360.0f };

	Uint32 m_FrameDelay{ 0 };

	Level m_Level;
	Avatar m_PlayerAvatar;
	Camera m_Camera;
	CollectibleManager m_CollectibleManager{ true };

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void UpdateFrameStats(float elapsedSec);
};