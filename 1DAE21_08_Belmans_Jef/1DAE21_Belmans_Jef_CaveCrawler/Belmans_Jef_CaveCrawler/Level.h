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

class Level final
{
public:
	Level(const Point2f& endBottomLeft);
	~Level();
	Level(const Level& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator= (Level&& other) = delete;
	
	void DrawLevel() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape) const;
	bool HasReachedEnd(const Rectf& actorShape) const;

	Rectf GetBoundaries() const;
	const std::vector<std::vector<Point2f>>& GetLevelVerts() const;

private:
	std::vector<std::vector<Point2f>> m_Verticies{};
	Texture* m_pBackgroundTexture{};
	Rectf m_Boundaries;
	LevelEnd m_LevelEnd;

	void LevelCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
};

