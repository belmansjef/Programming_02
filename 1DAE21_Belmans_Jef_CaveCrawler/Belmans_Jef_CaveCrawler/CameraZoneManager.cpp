#include "CameraZoneManager.h"
#include "CameraZone.h"
#include "utils.h"

CameraZoneManager::CameraZoneManager()
{
}

CameraZone* CameraZoneManager::AddItem(float left, float bottom, float width, float height)
{
	m_pItems.push_back(new CameraZone(left, bottom, width, height));
	return m_pItems.back();
}

Rectf CameraZoneManager::GetCurrentZone(const Rectf& actorShape) const
{
	for (CameraZone* zone : m_pItems)
	{
		if (zone->IsInZone(actorShape))
		{
			return zone->GetBoundaries();
		}
	}
	return Rectf{};
}