#pragma once

class Smiley;
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

	// CUSTOM MEMBERS
	static const int m_NrSmileys{ 10 };
	static Smiley* m_pSmileys[m_NrSmileys];

	Rectf m_SafeRect{};
	Rectf m_BoundingRect{};

	// CUSTOM FUNCTIONS
	void InitializeRects();
	void CreateSmileys();
	void DeleteSmileys();
	void DrawSmileys() const;
	void UpdateSmileys(float elapsedSec);
	void HitTestSmileys(const Point2f& hitPos) const;
	void DetermineHighestSmiley() const;
	void IncreaseSmileysSpeed() const;
	void DecreaseSmileysSpeed() const;
	void DeleteSleepers();
};