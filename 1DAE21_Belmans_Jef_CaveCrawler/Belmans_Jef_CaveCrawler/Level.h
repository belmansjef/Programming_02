#pragma once
#include "utils.h"

class Texture;

class Level
{
public:
	Level();
	~Level();
	
	void DrawBackground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape) const;
	Rectf GetBoundaries() const;

private:
	std::vector<std::vector<Point2f>> m_Verticies{};
	Texture* m_pBackgroundTexture{};
	Rectf m_Boundaries;

	void DrawVector(const Vector2f& v, const Point2f& startPos) const;
};

