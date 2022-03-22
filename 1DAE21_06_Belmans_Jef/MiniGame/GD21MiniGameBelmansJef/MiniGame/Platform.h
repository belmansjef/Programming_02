#pragma once
#include "pch.h"
#include "Vector2f.h"

class Texture;
class Platform
{
public:
	explicit Platform(const Point2f bottomLeft);
	Platform(const Platform& other);
	~Platform();

	Platform& operator=(const Platform& other);

	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

private:
	Rectf m_Shape{};
	Texture* m_pTexture{};
};

