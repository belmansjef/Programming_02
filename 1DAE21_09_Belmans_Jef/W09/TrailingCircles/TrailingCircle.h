#pragma once
#include "Vector2f.h"
#include <deque>

struct Trail
{
	float radius;
	float decrement;
	Color4f color;
	Point2f center;
	Trail(float radius, float decrement, Color4f color, Point2f center);
	void Update(float deltaTime);
};

class TrailingCircle
{
public:
	TrailingCircle( float radius, const Point2f& center);
	void Update( float elapsedSec, const Rectf& boundingRect );
	void Draw( ) const;

private:
	const float m_Radius;
	const Color4f m_Color;
	Point2f m_Center;
	Vector2f m_Velocity;

	std::deque<Trail*> m_pTrails;
	const int m_MaxTrails{ 10 };
	const float m_TrailSaveTime{ 0.08f };
	float m_ElapsedTime;

	Vector2f GetRandomVelocity( );
	Color4f GetRandomColor( );
	void UpdateTrails(float deltaTime);
};
