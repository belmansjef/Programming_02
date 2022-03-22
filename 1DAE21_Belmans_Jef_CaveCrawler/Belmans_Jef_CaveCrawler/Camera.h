#pragma once
#include "utils.h"

class Camera
{
public:
	Camera(float width, float height);
	
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void UpdatePosition(const Rectf& target, bool shouldTrack);
	void Transform() const;

private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;

	Point2f m_RawCameraPos;
	Point2f m_SmoothCameraPos;
	const float m_Smoothing{ 4.0f };

	Point2f Track(const Rectf& target) const;
	Point2f Clamp(const Point2f& bottomLeftPos) const;
};