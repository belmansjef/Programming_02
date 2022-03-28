#pragma once
#include "Level.h"
#include "Avatar.h"
#include "Camera.h"
#include "CollectibleManager.h"
#include "DamageBlockManager.h"

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

	bool m_ShouldPrintStats{ true };
	int m_Frames{ 0 };
	float m_FrameTime{ 0.0f };
	float m_AvgFrameTime{ 0.0f };
	float m_FrameRate{ 0.0f };
	const float m_MaxFPS{ 0.0f };

	Uint32 m_FrameDelay{ 0 };

	Level m_Level;
	Avatar m_PlayerAvatar{50.0f, 40.0f, 13.0f, 14.0f, 5};
	Camera m_Camera;
	CollectibleManager m_CollectibleManager;
	DamageBlockManager m_DamageBlockManager;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void UpdateFrameStats(float elapsedSec);
};