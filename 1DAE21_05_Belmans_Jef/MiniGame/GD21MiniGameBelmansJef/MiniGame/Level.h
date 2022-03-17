#pragma once
#include "utils.h"

class Texture;

class Level
{
public:
	Level();
	~Level();
	
	void DrawBackground() const;
	void DrawForeground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape) const;

	Rectf GetBoundaries();

private:
	std::vector<std::vector<Point2f>> m_Verticies;
	Texture* m_pBackgroundTexture;
	Texture* m_pFenceTexture;
	Point2f	m_FenceBottomLeft;

	Rectf m_Boundaries;

	void DrawVector(const Vector2f& v, const Point2f& startPos) const;
};

