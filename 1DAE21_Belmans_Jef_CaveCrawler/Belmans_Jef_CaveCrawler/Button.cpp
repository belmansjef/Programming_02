#include "pch.h"
#include "Button.h"
#include "utils.h"
#include "Texture.h"

Button::Button(const Point2f& bottomLeft, const std::string& text, const int fontSize, float width, float height)
	: m_IsHighlighted{ false }
	, m_Graphic
		{	Rectf
			{
				bottomLeft.x,
				bottomLeft.y,
				width,
				height
			}
		}
	 , m_pText{ new Texture(text, "Resources/Font.ttf", fontSize, Color4f(1.0f, 1.0f, 1.0f, 1.0f)) }
{
	 m_TextPos = Point2f(bottomLeft.x + (width / 2.0f) - m_pText->GetWidth() / 2.0f,
		 bottomLeft.y + (height / 2.0f) - m_pText->GetHeight() / 2.0f);
}

Button::~Button()
{
	 delete m_pText;
	 m_pText = nullptr;
}

bool Button::IsHighlighted() const
{
	return m_IsHighlighted;
}

void Button::SetHighlighted(bool isHighlighted)
{
	m_IsHighlighted = isHighlighted;
}

float Button::GetHeight() const
{
	return m_Graphic.height;
}

void Button::Reposition(const Point2f& newPos)
{
	m_Graphic.left = newPos.x;
	m_Graphic.bottom = newPos.y;

	m_TextPos = Point2f(newPos.x + (m_Graphic.width / 2.0f) - m_pText->GetWidth() / 2.0f,
		newPos.y + (m_Graphic.height / 2.0f) - m_pText->GetHeight() / 2.0f);
}

void Button::Draw() const
{
	utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	m_pText->Draw(m_TextPos);

	if (m_IsHighlighted)
	{
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	}
	utils::DrawRect(m_Graphic, 2.0f);
}