#include <fstream>
#include <sstream>
#include "pch.h"
#include "CameraZoneManager.h"
#include "CameraZone.h"
#include "FileReader.h"
#include "utils.h"

CameraZoneManager::~CameraZoneManager()
{
	for (CameraZone* zone : m_pItems)
	{
		delete zone;
		zone = nullptr;
	}
}

void CameraZoneManager::Initialize(const std::string& filePath)
{
	std::ifstream file{ filePath };

	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string line;
			std::getline(file, line, '>');

			Rectf rect{ FileReader::ToRectf(FileReader::GetAttributeValue("Rectf", line))};

			AddItem(rect);
		}
	}
}

CameraZone* CameraZoneManager::AddItem(const Rectf& zoneRect)
{
	m_pItems.push_back(new CameraZone(zoneRect));
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