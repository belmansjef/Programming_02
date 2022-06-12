#include "pch.h"
#include "LevelBase.h"
#include "Texture.h"
#include "SVGParser.h"
#include "MenuManager.h"
#include "SoundManager.h"
#include "Enums.h"

LevelEnd::LevelEnd()
	: LevelEnd(Point2f())
{
}

LevelEnd::LevelEnd(const Point2f& bottomLeft)
	: pTexture{ new Texture("./Resources/Images/Sprite_LevelEnd.png") }
	, shape{ Rectf (bottomLeft.x, bottomLeft.y, pTexture->GetWidth(), pTexture->GetHeight())}
{
}

LevelBase::LevelBase(const std::string& levelName, const Window& window, const Point2f& avatarStartPos, const Point2f& endBottomLeft, const std::string& texturePath, const std::string& collisionPath)
	: m_pBackgroundTexture{ new Texture(texturePath) }
	, m_LevelName { levelName }
	, m_LevelEnd { LevelEnd(endBottomLeft) }
	, m_PlayerAvatar{ avatarStartPos.x, avatarStartPos.y, 13.0f, 14.0f }
	, m_Camera{ window.width / m_ScaleFactor, window.height / m_ScaleFactor }
	, m_EndScreenOverlay{ Rectf(0.0f, 0.0f, window.width, window.height) }
{
	m_Boundaries = Rectf{ 0.0f, 0.0f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight()};
	SVGParser::GetVerticesFromSvgFile(collisionPath, m_Verticies);
}

LevelBase::~LevelBase()
{
	delete m_pBackgroundTexture;
	m_pBackgroundTexture = nullptr;

	delete m_LevelEnd.pTexture;
	m_LevelEnd.pTexture = nullptr;
}

std::string LevelBase::GetLevelName() const
{
	return m_LevelName;
}

void LevelBase::Reset()
{
	m_PlayerAvatar.Reset();
	m_Camera.Reset();
}

void LevelBase::Draw(const GameState& currentGameState) const
{
	glPushMatrix();
		glScalef(m_ScaleFactor, m_ScaleFactor, 1);
		m_Camera.Transform();
		m_pBackgroundTexture->Draw();
	glPopMatrix();

	glPushMatrix();
		glScalef(m_ScaleFactor, m_ScaleFactor, 1);
		m_Camera.Transform();
		glTranslatef(m_LevelEnd.shape.left, m_LevelEnd.shape.bottom, 0);
		m_LevelEnd.pTexture->Draw();
	glPopMatrix();

	glPushMatrix();
		glScalef(m_ScaleFactor, m_ScaleFactor, 1);
		m_Camera.Transform();
		m_PlayerAvatar.Draw();
	glPopMatrix();
	

	// Draw HUD and overlays after popping world view
	switch (currentGameState)
	{
		case GameState::InGame:
			break;
		case GameState::Finished:
			utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 0.75f));
			utils::FillRect(m_EndScreenOverlay);
			break;
	}
}

void LevelBase::Update(GameState& currentGameState, MenuManager& menuManager)
{
	// Updates
	m_PlayerAvatar.Update(*this, currentGameState);
	if (currentGameState != GameState::Dead)
	{
		m_Camera.UpdatePosition(m_PlayerAvatar.GetShape(), m_PlayerAvatar.ShouldTrack());
		m_Camera.SetCameraBounds(m_CameraZoneManager.GetCurrentZone(m_PlayerAvatar.GetShape()));
	}

	if (m_PlayerAvatar.GetIsDead() && currentGameState != GameState::Dead)
	{
		PlayerDied(currentGameState, menuManager);
	}

	if (HasReachedEnd(m_PlayerAvatar.GetShape()) && currentGameState != GameState::Finished)
	{
		PlayerFinished(currentGameState, menuManager);
	};
}

void LevelBase::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	LevelCollision(actorShape, actorVelocity);
}

bool LevelBase::IsOnGround(const Rectf& actorShape) const
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

bool LevelBase::HasReachedEnd(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_LevelEnd.shape);
}

Rectf LevelBase::GetBoundaries() const
{
	return m_Boundaries;
}

const std::vector<std::vector<Point2f>>& LevelBase::GetLevelVerts() const
{
	return m_Verticies;
}


void LevelBase::PlayerDied(GameState& currentGameState, MenuManager& menuManager)
{
	currentGameState = GameState::Dead;
	menuManager.OpenMenu(MenuType::GameOver);
}

void LevelBase::PlayerFinished(GameState& currentGameState, MenuManager& menuManager)
{
	Time::GetInstance()->m_TimeScale = 0.0f;
	currentGameState = GameState::Finished;
	menuManager.OpenMenu(MenuType::Finished);

	SoundManager::GetInstance()->PlaySound(SoundType::levelFinish);
}

void LevelBase::LevelCollision(Rectf& actorShape, Vector2f& actorVelocity) const
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