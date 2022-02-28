#pragma once
#include "Vector2f.h"

class DaeEllipse
{
public:
	DaeEllipse( const Point2f& center, float width, float height, const Color4f& color, bool isFilled );

	void Draw( ) const;
	void Translate( const Vector2f& tr );

private: 
	Point2f m_Center;
	float m_Width;
	float m_Height;
	Color4f m_Color;
	bool m_IsFilled;
};

 
