#pragma once
#include "structs.h"

class Camera final
{
public:
	Camera(float width, float height);
	~Camera() = default;
	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera& operator=(Camera&& other) = delete;
	
	void SetCameraBounds(const Rectf& cameraBounds);
	void UpdatePosition(const Rectf& target, bool shouldTrack);
	void Transform() const;

	void DoScreenShake();
	void Reset();

private:
	float m_Width;
	float m_Height;
	Rectf m_CameraBounds;

	Point2f m_RawCameraPos;
	Point2f m_SmoothCameraPos;
	bool m_DoSmoothing{ true };
	const float m_Smoothing{ 4.0f };
	const float m_SmoothCooldown{ 0.5f };
	float m_SmoothDisableTime{ -m_SmoothCooldown };

	// Screenshake
	bool m_DoScreenShake{ true };
	const float m_ScreenShakeTime{ 0.1f };
	float m_ScreenShakeTimer{ 0.0f };

	const float m_Amplitude{ 25.0f };
	const float m_HorizontalShift{ 35.0f };
	const float m_Frequency{ (2.0f * 3.14f) / 0.085f };
	float m_Angle{ 0.0f };

	void TempDisableSmoothing();

	Point2f Track(const Rectf& target) const;
	Point2f Clamp(const Point2f& bottomLeftPos) const;
};