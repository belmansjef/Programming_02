#include "pch.h"
#include "Camera.h"

Camera::Camera(float width, float height)
	: m_Width { width }
	, m_Height { height }
{
	m_LevelBoundaries = Rectf{ 0.0f, 0.0f, m_Width, m_Height };
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Rectf& target) const
{
	Point2f cameraPos{ Track(target) };
	Clamp(cameraPos);
	glTranslatef(-cameraPos.x, -cameraPos.y, 0);
}

Point2f Camera::Track(const Rectf& target) const
{
	return Point2f(target.left - (m_Width / 2.0f - target.width / 2.0f), target.bottom - (m_Height / 2.0f - target.height / 2.0f));
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}
	
	if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.width - m_Width;
	}

	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}

	if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.height - m_Height;
	}
}