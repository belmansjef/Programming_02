#pragma once
#include "utils.h"

class Camera
{
public:
	Camera(float width, float height);
	
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void UpdatePosition(const Rectf& target, bool shouldTrack);
	void Transform() const;

	void DoScreenShake();

private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;

	Point2f m_RawCameraPos;
	Point2f m_SmoothCameraPos;
	const float m_Smoothing{ 4.0f };

	// Screenshake
	bool m_DoScreenShake{ true };

	const float m_ScreenShakeTime{ 0.2f };
	float m_ScreenShakeTimer{ 0.0f };

	const float m_Amplitude{ 25.0f };
	const float m_HorizontalShift{ 35.0f };
	const float m_Frequency{ (2.0f * 3.14f) / 0.085f };
	float m_Angle{ 0.0f };

	Point2f Track(const Rectf& target) const;
	Point2f Clamp(const Point2f& bottomLeftPos) const;
};