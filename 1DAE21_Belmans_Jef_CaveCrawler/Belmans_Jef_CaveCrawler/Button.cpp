#include "Button.h"
#include "utils.h"

Button::Button(const Point2f& bottomLeft, float width, float height, std::string text)
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
	, m_pText{ new Texture(text, "Resources/Font.ttf", 24, Color4f(1.0f, 1.0f, 1.0f, 1.0f)) }
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

void Button::Draw() const
{
	utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	m_pText->Draw();

	if (m_IsHighlighted)
	{
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	}
	utils::DrawRect(m_Graphic);
}