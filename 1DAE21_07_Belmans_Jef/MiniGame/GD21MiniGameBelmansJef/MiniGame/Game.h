#pragma once
#include "Vector2f.h"
#include "Level.h"
#include "PowerUpManager.h"
#include "Avatar.h"
#include "Camera.h"
#include "HUD.h"

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
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

	Level m_Level;
	PowerUpManager m_PowerUpManager;
	Avatar m_Avatar;
	Camera m_Camera;
	HUD m_Hud;

	bool m_EndReached;
	Rectf m_EndScreenOverlay;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
	void ShowTestMessage( ) const;
	void AddPowerUps( );
	void DoCollisionTests( );
};