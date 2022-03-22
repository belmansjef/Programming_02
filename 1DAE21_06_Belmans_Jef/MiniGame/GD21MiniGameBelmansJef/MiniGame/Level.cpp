#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "SVGParser.h"
#include "Platform.h"

Level::Level()
	: m_pBackgroundTexture{new Texture("./Resources/Images/background.png")}
	, m_pFenceTexture { new Texture("./Resources/Images/Fence.png")}
	, m_pEndSignTexture { new Texture("./Resources/Images/EndSign.png")}
	, m_FenceBottomLeft{ Point2f(200.0f, 190.0f) }
	, m_pPlatform { new Platform(Point2f(300.0f, 300.0f))}
{
	SVGParser::GetVerticesFromSvgFile("Resources/Images/level.svg", m_Verticies);
	m_Boundaries = Rectf{ 0.0f, 0.0f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight() };
	m_EndSignShape = Rectf{ 730.0f, 224.0f, m_pEndSignTexture->GetWidth(), m_pEndSignTexture->GetHeight() };
}

Level::Level(const Level& other)
	: m_pBackgroundTexture{ new Texture("./Resources/Images/background.png") }
	, m_pFenceTexture{ new Texture("./Resources/Images/Fence.png") }
	, m_pEndSignTexture{ new Texture("./Resources/Images/EndSign.png") }
	, m_FenceBottomLeft{ other.m_FenceBottomLeft }
	, m_pPlatform{ other.m_pPlatform }
	, m_Boundaries{ other.m_Boundaries }
	, m_EndSignShape{ other.m_EndSignShape }
	, m_Verticies{ other.m_Verticies }
{
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	delete m_pFenceTexture;

	m_pBackgroundTexture = nullptr;
	m_pFenceTexture = nullptr;
}

Level& Level::operator=(const Level& other)
{
	m_pBackgroundTexture = new Texture("./Resources/Images/background.png");
	m_pFenceTexture = new Texture("./Resources/Images/Fence.png");
	m_pEndSignTexture = new Texture("./Resources/Images/EndSign.png");
	m_FenceBottomLeft = other.m_FenceBottomLeft;
	m_pPlatform = other.m_pPlatform;
	m_Boundaries = other.m_Boundaries;
	m_EndSignShape = other.m_EndSignShape;
	m_Verticies = other.m_Verticies;
}

void Level::DrawBackground() const
{
	glPushMatrix();
		glTranslatef(0, 0, 0);
		m_pBackgroundTexture->Draw();
		m_pPlatform->Draw();
	glPopMatrix();
}
		
void Level::DrawForeground() const
{
	glPushMatrix();
		glTranslatef(m_FenceBottomLeft.x, m_FenceBottomLeft.y, 0);
		m_pFenceTexture->Draw();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(m_EndSignShape.left, m_EndSignShape.bottom, 0);
		m_pEndSignTexture->Draw();
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

	m_pPlatform->HandleCollision(actorShape, actorVelocity);
}

bool Level::IsOnGround(const Rectf& actorShape, Vector2f& actorVeloicty) const
{
	const Point2f startPos{ actorShape.left + actorShape.width / 2.0f, actorShape.bottom + actorShape.height };
	const Point2f endPos{ startPos.x, startPos.y - (actorShape.height + 1.0f) };

	utils::HitInfo hitInfo;
	return utils::Raycast(m_Verticies[0], startPos, endPos, hitInfo) || m_pPlatform->IsOnGround(actorShape, actorVeloicty);
}

Rectf Level::GetBoundaries()
{
	return m_Boundaries;
}

bool Level::HasReachedEnd(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_EndSignShape);
}

void Level::DrawVector(const Vector2f& v, const Point2f& startPos) const
{
	const Point2f endPos{ startPos + v };
	utils::DrawLine(startPos, endPos);
}
