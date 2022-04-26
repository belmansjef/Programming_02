#include "pch.h"
#include "DaeShape.h"
#include <sstream>

DaeShape::DaeShape(const Point2f& center, float width, float height, const Color4f& color)
	: m_Center { center }
	, m_Width  { width  }
	, m_Height { height }
	, m_Color { color }
{
}

std::string DaeShape::PropertiesToString()
{
	std::stringstream ss;
	ss.precision(0);
	ss.setf(std::ios::fixed);
	ss << R"(Center=")" << m_Center.x << "," << m_Center.y << "\"\n"
		<< R"(Width=")" << m_Width << "\"\n"
		<< R"(Height=")" << m_Height << "\"\n";
	ss.precision(2);
	ss << R"(Color=")" << m_Color.r << "," << m_Color.g << "," << m_Color.b << "," << m_Color.a;
	
	return ss.str();
}

void DaeShape::Translate(const Vector2f& tr)
{
	m_Center += tr;
}
