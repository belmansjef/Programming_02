#pragma once
#include "pch.h"

class Enemy
{
public:
	Enemy();
	Enemy(const Point2f& center, float width, float height);
	~Enemy();

	void Draw() const;
	bool DoHitTest(const Rectf& other) const;
	bool IsDead() const;

	void SetCenter(const Point2f& center);
	void SetDimensions(float width, float height);

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	Rectf m_EnemyRect;
	bool m_IsDead;
};

