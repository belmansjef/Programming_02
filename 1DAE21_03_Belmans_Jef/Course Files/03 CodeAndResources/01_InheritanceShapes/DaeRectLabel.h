#pragma once
#include "Vector2f.h"
#include "Texture.h"

class DaeRectLabel  
{
public:
	DaeRectLabel( const Point2f& center, float width, float height, const Color4f& color, const std::string& label, const Color4f& textColor, TTF_Font* pFont );
	~DaeRectLabel( );


	void Draw( ) const;
	void Translate( const Vector2f& tr );

private: 
	Point2f m_Center;
	float m_Width;
	float m_Height;
	Color4f m_Color;
	Texture* m_pLabelText;
	float m_MarginX;
	float m_MarginY;
};

 
