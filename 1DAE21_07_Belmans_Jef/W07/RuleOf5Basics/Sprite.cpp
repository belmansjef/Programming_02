#include "pch.h"
#include "Sprite.h"
#include <iostream>
#include "Texture.h"

Sprite::Sprite( const std::string& path, int cols, int rows, float frameSec )
	: m_Cols( cols )
	, m_Rows( rows )
	, m_FrameSec( frameSec )
	, m_AccuSec{}
	, m_ActFrame{}
	, m_pTexture{ new Texture( path ) }
	, m_TexturePath { path }
{
}

Sprite::~Sprite( )
{
	std::cout << "Sprite dtr\n";
	delete m_pTexture;
}

Sprite::Sprite(const Sprite& other)
	: m_Cols { other.m_Cols }
	, m_Rows { other.m_Rows }
	, m_FrameSec { other.m_FrameSec }
	, m_AccuSec { other.m_AccuSec }
	, m_ActFrame { other.m_ActFrame }
	, m_TexturePath { other.m_TexturePath }
{
	std::cout << "Copy constructor\n";
	delete m_pTexture;
	m_pTexture = new Texture(m_TexturePath);
}

Sprite& Sprite::operator=(const Sprite& other)
{
	if (&other != this)
	{
		std::cout << "Copy assignment\n";
		delete m_pTexture;
		m_Cols = other.m_Cols;
		m_Rows = other.m_Rows;
		m_FrameSec = other.m_FrameSec;
		m_AccuSec = other.m_AccuSec;
		m_ActFrame = other.m_ActFrame;
		m_TexturePath = other.m_TexturePath;
		m_pTexture = new Texture(m_TexturePath);
	}

	return *this;
}

Sprite::Sprite(Sprite&& other) noexcept
	: m_Cols{ other.m_Cols }
	, m_Rows{ other.m_Rows }
	, m_FrameSec{ other.m_FrameSec }
	, m_AccuSec{ other.m_AccuSec }
	, m_ActFrame{ other.m_ActFrame }
	, m_TexturePath{ other.m_TexturePath }
	, m_pTexture { other.m_pTexture }
{
	std::cout << "Move constructor\n";
	other.m_pTexture = nullptr;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
	if (&other != this)
	{
		std::cout << "Move assignment\n";
		delete m_pTexture;
		m_Cols = other.m_Cols;
		m_Rows = other.m_Rows;
		m_FrameSec = other.m_FrameSec;
		m_AccuSec = other.m_AccuSec;
		m_ActFrame = other.m_ActFrame;
		m_TexturePath = other.m_TexturePath;
		m_pTexture = other.m_pTexture;
		
		other.m_pTexture = nullptr;
	}

	return *this;
}

void Sprite::Update( float elapsedSec )
{
	m_AccuSec += elapsedSec;

	if ( m_AccuSec > m_FrameSec )
	{
		// Go to next frame
		++m_ActFrame;
		if ( m_ActFrame >= m_Cols * m_Rows )
		{
			m_ActFrame = 0;
		}

		// Only keep the remaining time
		m_AccuSec -= m_FrameSec;
	}
}

void Sprite::Draw( const Point2f& pos, float scale )
{
	// frame dimensions
	const float frameWidth{  m_pTexture->GetWidth() / m_Cols };
	const float frameHeight{  m_pTexture->GetHeight() / m_Rows };
	int row = m_ActFrame / m_Cols;
	int col = m_ActFrame % m_Cols;

	Rectf srcRect;
	srcRect.height = frameHeight;
	srcRect.width = frameWidth;
	srcRect.left = m_ActFrame % m_Cols * srcRect.width;
	srcRect.bottom = m_ActFrame / m_Cols * srcRect.height + srcRect.height;
	Rectf destRect{ pos.x, pos.y,srcRect.width * scale,srcRect.height * scale };
	m_pTexture->Draw( destRect, srcRect );
}

float Sprite::GetFrameWidth( )
{
	return m_pTexture->GetWidth( ) / m_Cols;
}

float Sprite::GetFrameHeight( )
{
	return m_pTexture->GetHeight( ) / m_Rows;
}

