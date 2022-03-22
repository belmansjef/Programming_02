#include "pch.h"
#include "Camera.h"
#include "Game.h"

Camera::Camera(float width, float height)
	: m_Width { width }
	, m_Height { height }
	, m_RawCameraPos{ 0.0f, 0.0f }
	, m_SmoothCameraPos{ 0.0f, 0.0f }
{
	m_LevelBoundaries = Rectf{ 0.0f, 0.0f, m_Width, m_Height };
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::UpdatePosition(const Rectf& target, bool shouldTrack)
{
	if (shouldTrack)
	{
		m_RawCameraPos = Clamp(Track(target));	
	}
	
	m_SmoothCameraPos.x = std::lerp(m_SmoothCameraPos.x, m_RawCameraPos.x, m_Smoothing * Time::deltaTime);
	m_SmoothCameraPos.y = std::lerp(m_SmoothCameraPos.y, m_RawCameraPos.y, m_Smoothing * Time::deltaTime);
}

void Camera::Transform() const
{
	glTranslatef(-m_SmoothCameraPos.x, -m_SmoothCameraPos.y, 0);
}

Point2f Camera::Track(const Rectf& target) const
{
	return Point2f(target.left - (m_Width / 2.0f - target.width / 2.0f), target.bottom - (m_Height / 2.0f - target.height / 2.0f));
}

Point2f Camera::Clamp(const Point2f& bottomLeftPos) const
{
	Point2f clampedPos{ bottomLeftPos.x, bottomLeftPos.y };
	if (bottomLeftPos.x < m_LevelBoundaries.left)
	{
		clampedPos.x = m_LevelBoundaries.left;
	}
	
	if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		clampedPos.x = m_LevelBoundaries.width - m_Width;
	}

	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
	{
		clampedPos.y = m_LevelBoundaries.bottom;
	}

	if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		clampedPos.y = m_LevelBoundaries.height - m_Height;
	}

	return clampedPos;
}

