#pragma once
#include "pch.h"
class Texture;

class Card final
{
public:
	enum class Suit
	{
		clubs = 1,
		diamonds = 2,
		hearts = 3,
		spades = 4
	};

	explicit Card( Suit suit, int rank, float angle, const Circlef& movementPath );
	~Card();
	void Draw( ) const;
	void Update(float elapsedSec);

	static const int m_MinRank;
	static const int m_MaxRank;
	float GetWidth()const ;
	float GetHeight()const ;

private:
	float m_Angle;
	float m_Width;
	float m_Height;
	const float m_RotationalSpeed;
	const Circlef m_MovementPath;
	const Texture *m_pTexture;
	const Suit m_Suit;
	const int m_Rank;

	std::string GetImagePath(Suit suit, int rank) const;
};