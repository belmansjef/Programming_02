#include "pch.h"
#include "Card.h"
#include "Texture.h"

const int Card::m_MinRank{ 1 };
const int Card::m_MaxRank{ 13 };

Card::Card(Suit suit, int rank)
	: m_Suit{suit}
	, m_Rank{rank}
{
	m_pTexture = new Texture(GetImagePath(m_Suit, m_Rank));
	m_Height = m_pTexture->GetHeight();
	m_Width = m_pTexture->GetWidth();
}

Card::~Card()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Card::Draw(const Rectf& destRect) const
{
	m_pTexture->Draw(destRect);
}

float Card::GetWidth() const
{
	return m_Width;
}

float Card::GetHeight() const
{
	return m_Height;
}

std::string Card::GetImagePath(Suit suit, int rank) const
{
	return std::string("Resources/" + std::to_string((int(m_Suit) * 100) + m_Rank) + ".png");
}
