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
		m_pBackgroundTexture->Draw();
	glPopMatrix();
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const		
{
	utils::HitInfo hitInfo{};

	// Upward detection
	Point2f startPos{ actorShape.left + 1, actorShape.bottom + actorShape.height - 5 };
	Point2f endPos{ startPos.x, actorShape.bottom + actorShape.height };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height;
		actorVelocity.y = 0.0f;
	}

	startPos = Point2f { actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.height - 5};
	endPos = Point2f { startPos.x, actorShape.bottom + actorShape.height };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height;
		actorVelocity.y = 0.0f;
	}

	startPos = Point2f { actorShape.left + actorShape.width - 1, actorShape.bottom + actorShape.height - 5};
	endPos = Point2f { startPos.x, actorShape.bottom + actorShape.height };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height;
		actorVelocity.y = 0.0f;
	}

	// Downward detection
	startPos = Point2f{ actorShape.left + 1, actorShape.bottom + 5 };
	endPos = Point2f{ actorShape.left + 1, actorShape.bottom };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
	}

	startPos = Point2f { actorShape.left + actorShape.width / 2.0f, actorShape.bottom + 5 };
	endPos = Point2f { actorShape.left + actorShape.width / 2.0f, actorShape.bottom };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
	}

	startPos = Point2f{ actorShape.left + actorShape.width - 1, actorShape.bottom + 5 };
	endPos = Point2f{ actorShape.left + actorShape.width - 1, actorShape.bottom };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
	}

	// Forward detection
	startPos = Point2f{ actorShape.left + actorShape.width - 1, actorShape.bottom + actorShape.height};
	endPos = Point2f{ actorShape.left + actorShape.width, startPos.y };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
	}

	startPos = Point2f {actorShape.left + actorShape.width - 1, actorShape.bottom + actorShape.height / 2.0f};
	endPos = Point2f{ actorShape.left + actorShape.width, startPos.y };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
	}

	startPos = Point2f{ actorShape.left + actorShape.width - 1, actorShape.bottom};
	endPos = Point2f{ actorShape.left + actorShape.width, startPos.y };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
	}

	// Backward detection
	startPos = Point2f{ actorShape.left + 1, actorShape.bottom + actorShape.height / 2.0f };
	endPos = Point2f{ actorShape.left, startPos.y };
	if (utils::Raycast(m_Verticies[2], startPos, endPos, hitInfo))
	{
		actorShape.left = hitInfo.intersectPoint.x;
	}
}

bool Level::IsOnGround(const Rectf& actorShape) const
{
	utils::HitInfo hitInfo;

	Point2f startPosLeft { actorShape.left + 1, actorShape.bottom + actorShape.height / 2.0f };
	Point2f endPosLeft { startPosLeft.x, actorShape.bottom };

	Point2f startPosMid { actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.height / 2.0f };
	Point2f endPosMid { startPosMid.x, actorShape.bottom };

	Point2f startPosRight { actorShape.left + actorShape.width - 1, actorShape.bottom + actorShape.height / 2.0f };
	Point2f endPosRight { startPosRight.x, actorShape.bottom };


	return utils::Raycast(m_Verticies[2], startPosLeft, endPosLeft, hitInfo)
		|| utils::Raycast(m_Verticies[2], startPosMid, endPosMid, hitInfo)
		|| utils::Raycast(m_Verticies[2], startPosRight, endPosRight, hitInfo);
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
