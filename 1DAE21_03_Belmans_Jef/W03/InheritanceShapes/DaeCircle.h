#pragma once
#include "Vector2f.h"

class DaeCircle : public DaeEllipse
{
public:
	DaeCircle( const Point2f& center, float diameter, const Color4f& color, bool isFilled );

	void Draw( ) const;
	void Translate( const Vector2f& tr );

private: 
	Point2f m_Center;
	float m_Diameter;
	Color4f m_Color;
	bool m_IsFilled;
};

 
