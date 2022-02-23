#pragma once

class Enemy;
class Avatar;

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

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	// CUSTOM DATA MEMBERS
	static const int m_NrEnemies{ 40 };
	Enemy* m_pEnemies[m_NrEnemies];

	Avatar* m_pPlayer;

	// CUSTOM FUNCTIONS
	void CreateEnemies();
	void DrawEnemies() const;

	void CreatePlayer();
	void DrawPlayer() const;
	void UpdatePlayer(float elapsedSec) const;
};