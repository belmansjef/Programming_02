#pragma once
#include "utils.h"
#include "Avatar.h"
#include "Camera.h"
#include "CameraZoneManager.h"

class Texture;
class MenuManager;
class ScoreManager;

struct LevelEnd final
{
	LevelEnd();
	explicit LevelEnd(const Point2f& bottomLeft);

	Texture* pTexture;
	Rectf shape;
};

class LevelBase
{
public:
	LevelBase(const std::string& levelName, const Window& window, const Point2f& avatarStartPos, const Point2f& endBottomLeft, const std::string& texturePath, const std::string& collisionPath);
	virtual ~LevelBase();

	LevelBase(const LevelBase& other) = delete;
	LevelBase& operator=(const LevelBase& other) = delete;
	LevelBase(LevelBase&& other) = delete;
	LevelBase& operator= (LevelBase&& other) = delete;
	
	std::string GetLevelName() const;

	virtual void Reset();
	virtual void Draw(const GameState& currentGameState) const;
	virtual void Update(GameState& currentGameState, MenuManager& menuManager, ScoreManager& scoreManager);
	
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape) const;
	bool HasReachedEnd(const Rectf& actorShape) const;

	Rectf GetBoundaries() const;
	const std::vector<std::vector<Point2f>>& GetLevelVerts() const;

protected:
	const float m_ScaleFactor{ 4.0f };
	CameraZoneManager m_CameraZoneManager;
	Avatar m_PlayerAvatar;
	Camera m_Camera;
	virtual void PlayerFinished(GameState& currentGameState, MenuManager& menuManager, ScoreManager& scoreManager);

private:
	const std::string m_LevelName;
	std::vector<std::vector<Point2f>> m_Verticies{};
	
	Texture* m_pBackgroundTexture{};
	Rectf m_Boundaries;
	LevelEnd m_LevelEnd;
	Rectf m_EndScreenOverlay;
	
	void PlayerDied(GameState& currentGameState, MenuManager& menuManager);
	void LevelCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
};