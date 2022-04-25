#pragma once
#include "pch.h"
#include "Vector2f.h"

class Texture;
class Platform
{
public:
	explicit Platform(const Point2f bottomLeft);
	~Platform();

	Platform(const Platform& other);
	Platform& operator=(const Platform& other);
	Platform(Platform&& other) = delete;
	Platform& operator=(Platform&& other) = delete;

	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

private:
	Rectf m_Shape{};
	Texture* m_pTexture{};
};

