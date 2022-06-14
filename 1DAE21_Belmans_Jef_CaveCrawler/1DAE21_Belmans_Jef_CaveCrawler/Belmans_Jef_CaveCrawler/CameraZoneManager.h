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

	void Initialize(const std::string& filePath);
	CameraZone* AddItem(const Rectf& zoneRect);
	Rectf GetCurrentZone(const Rectf& actorShape) const;

private:
	std::vector<CameraZone*> m_pItems;
};

