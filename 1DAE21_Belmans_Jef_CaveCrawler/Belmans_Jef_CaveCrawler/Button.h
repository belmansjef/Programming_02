#pragma once
#include "structs.h"
#include "Texture.h"

class Button
{
public:
	Button(const Point2f& bottomLeft, float width, float height, std::string text);
	~Button();

	bool IsHighlighted() const;
	void SetHighlighted(bool isHighlighted);

	void Draw() const;

private:

	bool m_IsHighlighted;
	Rectf m_Graphic;
	Texture* m_pText;
	Point2f m_TextPos;
};

