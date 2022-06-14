#pragma once
#include "structs.h"
#include "Vector2f.h"

class Particle final
{
public:
	Particle() = default;
	
	bool IsAlive() const;

	void Initialize(const Vector2f& velocity, float startSize, float endSize, float lifetime);
	void Instantiate(const Point2f& position);
	void Reset();

	void Update();
	void Draw() const;

private:
	bool m_IsAlive;

	Point2f m_Position;
	Vector2f m_Velocity;

	float m_StartSize;
	float m_EndSize;
	float m_CurrentSize;
	float m_StartLifetime;
	float m_RemainingLifetime;

	Rectf m_Graphic;
};

