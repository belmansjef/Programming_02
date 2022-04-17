#pragma once
#include "utils.h"

class Texture;
class Level final
{
public:
	Level();
	~Level();
	Level(const Level& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator= (Level&& other) = delete;
	
	void DrawBackground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape) const;

	Rectf GetBoundaries() const;
	const std::vector<std::vector<Point2f>>& GetLevelVerts() const;

private:
	std::vector<std::vector<Point2f>> m_Verticies{};
	Texture* m_pBackgroundTexture{};
	Rectf m_Boundaries;

	void LevelCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
};

