#include "CameraZone.h"
#include "utils.h"

CameraZone::CameraZone(float left, float bottom, float width, float height)
	: m_Boundaries { Rectf(left, bottom, width, height) } 
{
}

bool CameraZone::IsInZone(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_Boundaries);
}

Rectf CameraZone::GetBoundaries() const
{
	return m_Boundaries;
}
