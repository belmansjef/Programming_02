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

private:
	std::vector<Point2f> m_Verticies{};
	Texture* m_pBackgroundTexture{};
	Texture* m_pFenceTexture{};
	Point2f	m_FenceBottomLeft{};

	void DrawVector(const Vector2f& v, const Point2f& startPos) const;
};

