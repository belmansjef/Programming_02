#pragma once
#include "pch.h"
#include "Vector2f.h"

class Texture;
class Platform
{
public:
	Platform(const Point2f bottomLeft);
	~Platform();

	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

private:
	Rectf m_Shape{};
	Texture* m_pTexture{};
};

