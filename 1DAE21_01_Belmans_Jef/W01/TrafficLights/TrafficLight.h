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
	void DoHitTest(const Point2f& point) const;
	float GetWidth() const;
	float GetHeight() const;

	static float m_AccumulatedSec;

private:
	State m_State{};
	const Point2f m_Position{};

	// Graphics
	const Circlef m_RedLight;
	const Circlef m_OrangeLight;
	const Circlef m_GreenLight;
	const Rectf m_Armature;
};

