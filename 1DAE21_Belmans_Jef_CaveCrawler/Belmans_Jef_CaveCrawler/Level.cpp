#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "SVGParser.h"

Level::Level()
	:m_pBackgroundTexture{ new Texture("Resources/Images/Level_1.png") }
{
	m_Boundaries = Rectf{ 0.0f, 0.0f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight()};
	SVGParser::GetVerticesFromSvgFile("Resources/Images/Level_1.svg", m_Verticies);
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	m_pBackgroundTexture = nullptr;
}

void Level::DrawBackground() const
{
	glPushMatrix();
		glTranslatef(0, 0, 0);
		m_pBackgroundTexture->Draw();
	glPopMatrix();
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const		
{
	LevelCollision(actorShape, actorVelocity);
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

	bool isGrounded{false};
	for (size_t i = 0; i < m_Verticies.size(); i++)
	{
		isGrounded |=
			utils::Raycast(m_Verticies[i], startPosLeft, endPosLeft, hitInfo)
			|| utils::Raycast(m_Verticies[i], startPosMid, endPosMid, hitInfo)
			|| utils::Raycast(m_Verticies[i], startPosRight, endPosRight, hitInfo);
	}

	return isGrounded;
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

const std::vector<std::vector<Point2f>>& Level::GetLevelVerts() const
{
	return m_Verticies;
}

void Level::LevelCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	const int rayLength{ 8 };
	const int rayOffset{ 3 };
	utils::HitInfo hitInfo{};

	// Backward detection
	Point2f startPos = Point2f{ actorShape.left + rayLength, actorShape.bottom + actorShape.height - rayOffset };
	Point2f endPos = Point2f{ actorShape.left, startPos.y };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.left = hitInfo.intersectPoint.x;
		}
	}

	startPos = Point2f{ actorShape.left + rayLength, actorShape.bottom + actorShape.height / 2.0f };
	endPos = Point2f{ actorShape.left, startPos.y };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.left = hitInfo.intersectPoint.x;
		}
	}

	startPos = Point2f{ actorShape.left + rayLength, actorShape.bottom + rayOffset };
	endPos = Point2f{ actorShape.left, startPos.y };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.left = hitInfo.intersectPoint.x;
		}
	}

	// Forward detection
	startPos = Point2f{ actorShape.left + actorShape.width - rayLength, actorShape.bottom + actorShape.height - rayOffset };
	endPos = Point2f{ actorShape.left + actorShape.width, startPos.y };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
		}
	}

	startPos = Point2f{ actorShape.left + actorShape.width - rayLength, actorShape.bottom + actorShape.height / 2.0f };
	endPos = Point2f{ actorShape.left + actorShape.width, startPos.y };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
		}
	}

	startPos = Point2f{ actorShape.left + actorShape.width - rayLength, actorShape.bottom + rayOffset };
	endPos = Point2f{ actorShape.left + actorShape.width, startPos.y };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
		}
	}

	// Upward detection
	startPos = Point2f{ actorShape.left + 1, actorShape.bottom + actorShape.height - rayLength };
	endPos = Point2f{ startPos.x, actorShape.bottom + actorShape.height };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height;
			actorVelocity.y = 0.0f;
		}
	}

	startPos = Point2f{ actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.height - rayLength };
	endPos = Point2f{ startPos.x, actorShape.bottom + actorShape.height };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height;
			actorVelocity.y = 0.0f;
		}
	}

	startPos = Point2f{ actorShape.left + actorShape.width - 1, actorShape.bottom + actorShape.height - rayLength };
	endPos = Point2f{ startPos.x, actorShape.bottom + actorShape.height };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height;
			actorVelocity.y = 0.0f;
		}
	}

	// Downward detection
	startPos = Point2f{ actorShape.left + 1, actorShape.bottom + 5 };
	endPos = Point2f{ actorShape.left + 1, actorShape.bottom };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
		}
	}

	startPos = Point2f{ actorShape.left + actorShape.width / 2.0f, actorShape.bottom + rayLength };
	endPos = Point2f{ actorShape.left + actorShape.width / 2.0f, actorShape.bottom };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
		}
	}

	startPos = Point2f{ actorShape.left + actorShape.width - 1, actorShape.bottom + rayLength };
	endPos = Point2f{ actorShape.left + actorShape.width - 1, actorShape.bottom };
	for (std::vector<Point2f> verts : m_Verticies)
	{
		if (utils::Raycast(verts, startPos, endPos, hitInfo))
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
		}
	}
}

void Level::DrawVector(const Vector2f& v, const Point2f& startPos) const
{
	const Point2f endPos{ startPos + v };
	utils::DrawLine(startPos, endPos);
}