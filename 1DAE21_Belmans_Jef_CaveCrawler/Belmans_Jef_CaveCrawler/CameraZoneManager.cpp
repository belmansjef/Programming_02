#include "CameraZoneManager.h"
#include "CameraZone.h"
#include "utils.h"
#include "pch.h"

CameraZoneManager::~CameraZoneManager()
{
	for (CameraZone* zone : m_pItems)
	{
		delete zone;
		zone = nullptr;
	}
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

	std::cout << "Error getting camerazone!" << std::endl;
	return Rectf{};
}