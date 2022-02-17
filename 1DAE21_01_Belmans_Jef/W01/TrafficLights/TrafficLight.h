#pragma once
#include "pch.h"

class TrafficLight
{
	enum class State
	{
		green,
		orange,
		red,
		off
	};

public:
	TrafficLight(const Point2f& pos);
	void Update(float elapsedSec);
	void Draw();
	void DoHitTest(const Point2f& point);
	float GetWidth() const;
	float GetHeight() const;

private:
	State m_State{};
	const Point2f m_Position{};
	float m_AccumulatedSec;

	// Graphics
	const Circlef* m_pRedLight;
	const Circlef* m_pOrangeLight;
	const Circlef* m_pGreenLight;
	const Rectf* m_pArmature;
};

