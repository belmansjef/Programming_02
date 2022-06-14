#pragma once
#include "structs.h"

class Texture;
class Button final
{
public:
	Button(const Point2f& bottomLeft, const std::string& text, const int fontSize = 24, float width = 180.0f, float height = 40.0f);
	~Button();

	Button(const Button& other) = delete;
	Button& operator= (const Button& other) = delete;
	Button(Button&& other) = delete;
	Button& operator= (Button&& other) = delete;

	bool IsHighlighted() const;
	void SetHighlighted(bool isHighlighted);

	float GetHeight() const;
	float GetWidth() const;

	void Reposition(const Point2f& newPos);
	void Draw() const;

private:

	bool m_IsHighlighted;
	Texture* m_pText;
	Rectf m_Graphic;
	Point2f m_TextPos;
};

