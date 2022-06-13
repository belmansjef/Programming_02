#pragma once
#include "Avatar.h"
#include "Camera.h"
#include "MenuManager.h"
#include "LevelManager.h"
#include "HUD.h"
#include "ScoreManager.h"

enum class GameState;
class Game final
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void SetDoQuit(bool shouldQuit);
	bool GetDoQuit() const;
	void SetGameState(const GameState& state);
	void BackToMainMenu();
	void OpenOptionsMenu();

	void ResetScore();

	void LoadLevelByName(const std::string& levelName);
	void LoadNextLevel();

	void Update(float elapsedSec);
	void Draw() const;

	void ResetLevel();

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
	bool m_DoQuit;

	HUD m_HUD;
	GameState m_CurrentGameState;
	LevelManager m_LevelManager;
	ScoreManager m_ScoreManager;
	MenuManager m_MenuManager;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
};