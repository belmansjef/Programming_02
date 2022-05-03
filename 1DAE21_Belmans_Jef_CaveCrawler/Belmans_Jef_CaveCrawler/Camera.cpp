#include "Camera.h"
#include "pch.h"
#include "utils.h"

bool Camera::m_DoScreenShake{ false };
const float Camera::m_ScreenShakeTime{ 0.1f };
float Camera::m_ScreenShakeTimer{ 0.0f };

Camera::Camera(float width, float height)
	: m_Width { width }
	, m_Height { height }
	, m_RawCameraPos{ 0.0f, 0.0f }
	, m_SmoothCameraPos{ 0.0f, 0.0f }
{
	m_CameraBounds = Rectf{ 0.0f, 0.0f, m_Width, m_Height };
}

void Camera::SetCameraBounds(const Rectf& cameraBounds)
{
	if (cameraBounds.left != m_CameraBounds.left || cameraBounds.bottom != m_CameraBounds.bottom)
	{
		TempDisableSmoothing();	
	}

	m_CameraBounds = cameraBounds;
}

void Camera::UpdatePosition(const Rectf& target, bool shouldTrack)
{
	if (m_SmoothDisableTime + m_SmoothCooldown <= Time::time && !m_DoSmoothing) // Re-enable smoothing after cooldown
	{
		m_DoSmoothing = true;
	}

	if (shouldTrack || m_DoScreenShake)
	{
		m_RawCameraPos = Clamp(Track(target));
		if (m_ScreenShakeTimer <= 0.0f ) m_DoScreenShake = false;
	}
	
	if (m_DoScreenShake && m_DoSmoothing)
	{
		m_Angle += 1.0f * Time::deltaTime;
		if (m_Angle > 360.0f)
		{
			m_Angle = 0.0f;
		}
		m_RawCameraPos.x = m_RawCameraPos.x + sin(m_Frequency * m_Angle) * m_Amplitude;
		m_RawCameraPos.y = m_RawCameraPos.y + sin(m_Frequency * (m_Angle + m_HorizontalShift)) * m_Amplitude;

		m_ScreenShakeTimer -= Time::deltaTime;
	}

	if (m_DoSmoothing)
	{
		m_SmoothCameraPos.x = std::lerp(m_SmoothCameraPos.x, m_RawCameraPos.x, m_Smoothing * Time::deltaTime);
		m_SmoothCameraPos.y = std::lerp(m_SmoothCameraPos.y, m_RawCameraPos.y, m_Smoothing * Time::deltaTime);
	}
	else
	{
		m_SmoothCameraPos = m_RawCameraPos;
	}
}

void Camera::Transform() const
{
	glTranslatef(-m_SmoothCameraPos.x, -m_SmoothCameraPos.y, 0);
}

void Camera::DoScreenShake()
{
	m_DoScreenShake = true;
	m_ScreenShakeTimer = m_ScreenShakeTime;
}

void Camera::Reset()
{
	m_DoScreenShake = false;
}

void Camera::TempDisableSmoothing()
{
	m_SmoothDisableTime = Time::time;
	m_DoSmoothing = false;
}

Point2f Camera::Track(const Rectf& target) const
{
	return Point2f(target.left - (m_Width / 2.0f - target.width / 2.0f), target.bottom - (m_Height / 2.0f - target.height / 2.0f));
}

Point2f Camera::Clamp(const Point2f& bottomLeftPos) const
{
	Point2f clampedPos{ bottomLeftPos.x, bottomLeftPos.y };
	if (bottomLeftPos.x < m_CameraBounds.left)
	{
		clampedPos.x = m_CameraBounds.left;
	}
	
	if (bottomLeftPos.x + m_Width > m_CameraBounds.left + m_CameraBounds.width)
	{
		clampedPos.x = m_CameraBounds.left + m_CameraBounds.width - m_Width;
	}

	if (bottomLeftPos.y < m_CameraBounds.bottom)
	{
		clampedPos.y = m_CameraBounds.bottom;
	}

	if (bottomLeftPos.y + m_Height > m_CameraBounds.bottom + m_CameraBounds.height)
	{
		clampedPos.y = m_CameraBounds.bottom + m_CameraBounds.height - m_Height;
	}

	return clampedPos;
}


