#pragma once
#include "utils.h"

class Texture;
struct LevelEnd final
{
	LevelEnd();
	explicit LevelEnd(const Point2f& bottomLeft);

	Texture* pTexture;
	Rectf shape;
};

class Level
{
public:
	Level(const std::string& levelName, const Point2f& endBottomLeft, const std::string& texturePath, const std::string& collisionPath);
	virtual ~Level();

	Level(const Level& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator= (Level&& other) = delete;
	
	std::string GetLevelName() const;

	virtual void DrawLevel() const;
	virtual void Update() = 0;

	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape) const;
	bool HasReachedEnd(const Rectf& actorShape) const;

	Rectf GetBoundaries() const;
	const std::vector<std::vector<Point2f>>& GetLevelVerts() const;

private:
	const std::string m_LevelName;
	std::vector<std::vector<Point2f>> m_Verticies{};
	Texture* m_pBackgroundTexture{};
	Rectf m_Boundaries;
	LevelEnd m_LevelEnd;

	void LevelCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
};