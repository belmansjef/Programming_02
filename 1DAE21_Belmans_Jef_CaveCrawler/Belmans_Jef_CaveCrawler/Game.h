#pragma once
#include "Level.h"
#include "Avatar.h"
#include "Camera.h"
#include "CollectibleManager.h"
#include "DamageBlockManager.h"
#include "CameraZoneManager.h"
#include "RisingHandManager.h"
#include "CrabEnemyManager.h"
#include "Lava.h"

class Game final
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	// DATA MEMBERS
	const Window m_Window;
	const float m_ScaleFactor{ 4.0f };

	bool m_ShouldPrintStats{ true };
	float m_FrameTime{ 0.0f };
	float m_AvgFrameTime{ 0.0f };
	float m_FrameRate{ 0.0f };
	const int m_MaxFPS{ 5000 };
	const int m_MaxFrameTime{ 1000 / m_MaxFPS };

	Uint32 m_FrameDelay{ 0 };

	Level m_Level{Point2f(32.0f, 232.0f)};
	Avatar m_PlayerAvatar{ 48.0f, 24.0f, 13.0f, 14.0f };
	Camera m_Camera;
	CollectibleManager m_CollectibleManager;
	DamageBlockManager m_DamageBlockManager;
	CameraZoneManager m_CameraZoneManager;
	RisingHandManager m_RisingHandManager;
	CrabEnemyManager m_CrabEnemyManager;
	Lava m_Lava{Point2f(432.0f, 0.0f), 32.0f, 16.0f};

	bool m_HasReachedEnd{ false };
	Rectf m_EndScreenOverlay;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void ResetLevel();
	void UpdateFrameStats();
};