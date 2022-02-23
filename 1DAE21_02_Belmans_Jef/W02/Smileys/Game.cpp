#include <iostream>
#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "Texture.h"
#include "Smiley.h"

Smiley* Game::m_pSmileys[Game::m_NrSmileys];

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
	InitializeRects();
	CreateSmileys();
}

void Game::Cleanup( )
{
	DeleteSmileys();
}

void Game::Update( float elapsedSec )
{
	UpdateSmileys(elapsedSec);
	DetermineHighestSmiley();
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawSmileys();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		IncreaseSmileysSpeed();
		break;
	case SDLK_DOWN:
		DecreaseSmileysSpeed();
		break;
	case SDLK_DELETE:
		DeleteSleepers();
		break;
	default:
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{

}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	const Point2f mousePos
	{
		float(e.x),
		float(e.y)
	};

	HitTestSmileys(mousePos);
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ClearBackground( ) const
{
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitializeRects()
{
	m_BoundingRect = Rectf
	{
		0.0f,
		0.0f,
		m_Window.width,
		m_Window.height
	};

	m_SafeRect = Rectf
	{
		30.0f,
		30.0f,
		m_Window.width - 60.0f,
		m_Window.height - 60.0f
	};
}

void Game::CreateSmileys()
{
	Texture* m_pSmileyTexture = new Texture("Resources/Smileys.png");
	const float smileyWidth = m_pSmileyTexture->GetWidth() / 4.0f;
	delete m_pSmileyTexture;
	m_pSmileyTexture = nullptr;

	for (int i = 0; i < m_NrSmileys; i++)
	{
		m_pSmileys[i] = new Smiley(Point2f(((m_Window.width / 2.0f) - (smileyWidth * 5.0f) - 45.0f) + ((smileyWidth + 10.0f) * i) , m_Window.height / 2.0f));
	}
}

void Game::DeleteSmileys()
{
	for (Smiley* smiley : m_pSmileys)
	{
		delete smiley;
		smiley = nullptr;
	}
}

void Game::DrawSmileys() const
{
	utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
	utils::DrawRect(m_SafeRect);

	for (Smiley* smiley : m_pSmileys)
	{
		smiley->Draw();
	}
}

void Game::UpdateSmileys(float elapsedSec)
{
	for (Smiley* smiley : m_pSmileys)
	{
		smiley->Update(elapsedSec, m_BoundingRect, m_SafeRect);
	}
}

void Game::HitTestSmileys(const Point2f& hitPos) const
{
	for (Smiley* smiley : m_pSmileys)
	{
		smiley->HitTest(hitPos);
	}
}

void Game::DetermineHighestSmiley() const
{
	float highest{ 0.0f };
	int highestIndex{ 0 };

	for (int i = 0; i < m_NrSmileys; i++)
	{
		if (!m_pSmileys[i]->IsSleeping())
		{
			m_pSmileys[i]->SetHighest(false);
			if (highest < m_pSmileys[i]->GetPosition().y)
			{
				highest = m_pSmileys[i]->GetPosition().y;
				highestIndex = i;
			}
		}
	}

	m_pSmileys[highestIndex]->SetHighest(true);
}

void Game::IncreaseSmileysSpeed() const
{
	for (Smiley* smiley : m_pSmileys)
	{
		smiley->IncreaseSpeed();
	}
}

void Game::DecreaseSmileysSpeed() const
{
	for (Smiley* smiley : m_pSmileys)
	{
		smiley->DecreaseSpeed();
	}
}

void Game::DeleteSleepers()
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (!smiley) continue;

		if (smiley->IsSleeping())
		{
			delete smiley;
			smiley = nullptr;
		}
	}
}
