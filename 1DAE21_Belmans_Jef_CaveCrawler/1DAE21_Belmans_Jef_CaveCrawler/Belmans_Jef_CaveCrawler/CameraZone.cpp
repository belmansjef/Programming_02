#include "CameraZone.h"
#include "utils.h"

CameraZone::CameraZone(const Rectf& zoneRect)
	: m_Boundaries { zoneRect }
{
}

CameraZone::CameraZone(float left, float bottom, float width, float height)
	: CameraZone(Rectf(left, bottom, width, height))
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
