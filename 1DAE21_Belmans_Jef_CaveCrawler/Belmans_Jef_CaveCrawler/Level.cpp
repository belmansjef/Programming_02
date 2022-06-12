#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "SVGParser.h"

LevelEnd::LevelEnd()
	: LevelEnd(Point2f())
{
}

LevelEnd::LevelEnd(const Point2f& bottomLeft)
	: pTexture{ new Texture("./Resources/Images/Sprite_LevelEnd.png") }
	, shape{ Rectf (bottomLeft.x, bottomLeft.y, pTexture->GetWidth(), pTexture->GetHeight())}
{
}

Level::Level(const Point2f& endBottomLeft, const std::string& texturePath, const std::string& collisionPath)
	: m_pBackgroundTexture{ new Texture(texturePath) }
	, m_LevelEnd { LevelEnd(endBottomLeft) }
{
	m_Boundaries = Rectf{ 0.0f, 0.0f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight()};
	SVGParser::GetVerticesFromSvgFile(collisionPath, m_Verticies);
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	m_pBackgroundTexture = nullptr;

	delete m_LevelEnd.pTexture;
	m_LevelEnd.pTexture = nullptr;
}

void Level::DrawLevel() const
{
	glPushMatrix();
		glTranslatef(-16, -16, 0); // offset to background
		m_pBackgroundTexture->Draw();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(m_LevelEnd.shape.left, m_LevelEnd.shape.bottom, 0);
		m_LevelEnd.pTexture->Draw();
	glPopMatrix();
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const		
{
	LevelCollision(actorShape, actorVelocity);
}

bool Level::IsOnGround(const Rectf& actorShape) const
{
	utils::HitInfo hitInfo;

	Point2f startPosLeft { actorShape.left + 1, actorShape.bottom + actorShape.height / 3.0f };
	Point2f endPosLeft { startPosLeft.x, actorShape.bottom };

	Point2f startPosMid { actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.height / 3.0f };
	Point2f endPosMid { startPosMid.x, actorShape.bottom };

	Point2f startPosRight { actorShape.left + actorShape.width - 1, actorShape.bottom + actorShape.height / 3.0f };
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

bool Level::HasReachedEnd(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_LevelEnd.shape);
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