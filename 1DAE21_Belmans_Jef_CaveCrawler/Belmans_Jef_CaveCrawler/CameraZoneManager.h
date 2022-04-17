#pragma once
#include <vector>
#include "structs.h"

class CameraZone;
class CameraZoneManager final
{
public:
	CameraZoneManager() = default;
	~CameraZoneManager();
	CameraZoneManager(const CameraZoneManager& other) = delete;
	CameraZoneManager& operator=(const CameraZoneManager& other) = delete;
	CameraZoneManager(CameraZoneManager&& other) = delete;
	CameraZoneManager& operator=(CameraZoneManager&& other) = delete;

	CameraZone* AddItem(float left, float bottom, float width, float height);
	Rectf GetCurrentZone(const Rectf& actorShape) const;

private:
	std::vector<CameraZone*> m_pItems;
};

