#pragma once
#include <vector>
#include "structs.h"

class Texture;

class FallingSpike final
{
public:
	FallingSpike(const Point2f& bottomLeft);
	~FallingSpike();

	FallingSpike(const FallingSpike& other) = delete;
	FallingSpike& operator=(const FallingSpike& other) = delete;
	FallingSpike(FallingSpike&& other) = delete;
	FallingSpike& operator=(FallingSpike&& other) = delete;

	bool IsDestroyed() const;
	bool IsFalling() const;
	bool IsOverlapping(const Rectf& actorShape) const;
	bool IsOverlapping(const std::vector<Point2f>& polygon);

	void Destroy();

	void Update(const Rectf& actorShape);
	void Draw() const;
	void Reset();

private:
	Rectf m_BoxCollider;
	Texture* m_pTexture;
	Point2f m_StartPos;

	const Point2f m_TriggerDistance{ 24.0f, 128.0f };
	bool m_IsFalling{ false };
	bool m_IsDestroyed{ false };
	float m_VelocityY{ 0.0f };
	float m_Gravity{ -981.0f };
};