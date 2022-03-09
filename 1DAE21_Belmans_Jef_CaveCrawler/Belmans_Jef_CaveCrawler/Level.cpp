#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "SVGParser.h"

Level::Level()
	:m_pBackgroundTexture{ new Texture("Resources/Images/Level_Test.png") }
{
	m_Boundaries = Rectf{ 0.0f, 0.0f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight()};
	SVGParser::GetVerticesFromSvgFile("Resources/Images/Level_Test.svg", m_Verticies);
}

Level::~Level()
{
	delete m_pBackgroundTexture;

	m_pBackgroundTexture = nullptr;
}

void Level::DrawBackground() const
{
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		m_pBackgroundTexture->Draw();
	glPopMatrix();
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const		
{
	const Point2f startPos{ actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.height };
	const Point2f endPos{ startPos.x, startPos.y - actorShape.height };

	utils::HitInfo hitInfo{};
	if (utils::Raycast(m_Verticies[0], startPos, endPos, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
	}
}

bool Level::IsOnGround(const Rectf& actorShape) const
{
	const Point2f startPos{ actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.height };
	const Point2f endPos{ startPos.x, startPos.y - (actorShape.height + 1.0f) };

	utils::HitInfo hitInfo;
	return utils::Raycast(m_Verticies[0], startPos, endPos, hitInfo);
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

void Level::DrawVector(const Vector2f& v, const Point2f& startPos) const
{
	const Point2f endPos{ startPos + v };
	utils::DrawLine(startPos, endPos);
}
