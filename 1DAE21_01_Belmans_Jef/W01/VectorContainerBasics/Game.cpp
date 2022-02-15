#include "pch.h"
#include "Game.h"
#include "Card.h"

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
	for (int suit = 1; suit <= int(Card::Suit::spades); suit++)
	{
		for (int rank = Card::m_MinRank; rank <= Card::m_MaxRank; rank++)
		{
			m_Cards.push_back(new Card(Card::Suit(suit), rank));
		}
	}
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	const int cols{ Card::m_MaxRank };
	for (int i = 0; i < m_Cards.size(); i++)
	{
		const Rectf dstRect
		{
			(i % cols) * m_Cards[i]->GetWidth() / 4.0f,
			m_Window.height - ((i / cols) + 1) * m_Cards[i]->GetHeight() / 2.0f,
			m_Cards[i]->GetWidth() / 2.0f,
			m_Cards[i]->GetHeight() / 2.0f
		};

		m_Cards[i]->Draw(dstRect);
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	// std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	// Plus doesn't work on qwerty, requires shift
	case SDLK_EQUALS:
		m_Numbers.push_back(rand() % 30);
		PrintElements(m_Numbers);
		break;
	case SDLK_MINUS:
		if (m_Numbers.empty()) return;
		
		m_Numbers.pop_back();
		PrintElements(m_Numbers);
		break;
	case SDLK_UP:
		IncrementElements(m_Numbers, false);
		PrintElements(m_Numbers);
		break;
	case SDLK_DOWN:
		IncrementElements(m_Numbers, true);
		PrintElements(m_Numbers);
		break;
	case SDLK_s:
		ShuffleElements(m_Cards);
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::PrintElements(const vector<int> numbers)
{
	/*for (int i = 0; i < numbers.size(); i++)
	{
		cout << numbers[i] << " ";
	}*/

	for (int num : numbers)
	{
		cout << num << " ";
	}
	cout << endl;
}

void Game::IncrementElements(vector<int>& numbers, bool doNegativeIncrement)
{
	const int increment{ doNegativeIncrement ? -1 : 1 };

	for (int i = 0; i < numbers.size(); i++)
	{
		numbers[i] += increment;
	}
}

void Game::ShuffleElements(vector<Card*>& cards)
{
	for(int i = int(cards.size()) - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);

		Swap(cards[i], cards[j]);
	}
}

void Game::Swap(Card* a, Card* b)
{
	Card* temp = a;
	a = b;
	b = temp;
}
