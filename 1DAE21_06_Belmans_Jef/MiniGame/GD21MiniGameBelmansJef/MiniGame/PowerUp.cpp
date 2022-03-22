#include "pch.h"
#include "PowerUp.h"
#include "utils.h"
#include "Texture.h"

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type)
	: m_Type{ type }
	, m_pTexture{ new Texture{"./Resources/Images/PowerUp.png" } }
	, m_TextClip
	{
		0.0f,
		m_Type == Type::brown ? 0.0f : m_pTexture->GetHeight() / 2.0f,
		m_pTexture->GetWidth(),
		m_pTexture->GetHeight() / 2.0f
	}
	, m_RotSpeed{ 360.0f }
	, m_Angle{ 0.0f }
{
	m_Shape = Circlef(center, m_pTexture->GetWidth() / 2.0f);
}

PowerUp::PowerUp(const PowerUp& other)
	: m_Type{ other.m_Type }
	, m_pTexture{ new Texture("./Resources/Images/PowerUp.png")}
	, m_TextClip{ other.m_TextClip }
	, m_RotSpeed{ other.m_RotSpeed }
	, m_Angle{ other.m_Angle }
	, m_Shape{ other.m_Shape }
{
}

PowerUp::~PowerUp()
{
	delete m_pTexture;
	m_pTexture = nullptr;
	// std::cout << "Destroyed " << this << " PowerUp!" << std::endl;
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += m_RotSpeed * elapsedSec;
}

void PowerUp::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
		glRotatef(m_Angle, 0, 0, 1);
		glTranslatef(-m_Shape.radius, -m_Shape.radius, 0);
		m_pTexture->Draw(Point2f(), m_TextClip);
	glPopMatrix();
}

bool PowerUp::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}
