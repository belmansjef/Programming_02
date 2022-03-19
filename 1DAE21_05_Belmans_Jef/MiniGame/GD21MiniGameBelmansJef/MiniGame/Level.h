#pragma once
#include "utils.h"

class Texture;
class Platform;
class Level
{
public:
	Level();
	~Level();
	
	void DrawBackground() const;
	void DrawForeground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const;

	Rectf GetBoundaries();

	bool HasReachedEnd(const Rectf& actorShape) const;

private:
	std::vector<std::vector<Point2f>> m_Verticies;
	Texture* m_pBackgroundTexture;
	Texture* m_pFenceTexture;
	Texture* m_pEndSignTexture;
	Point2f	m_FenceBottomLeft;

	Rectf m_EndSignShape;

	Rectf m_Boundaries;
	Platform* m_pPlatform;

	void DrawVector(const Vector2f& v, const Point2f& startPos) const;
};

