#include <fstream>
#include <sstream>
#include "FallingSpikeManager.h"
#include "FallingSpike.h"
#include "Health.h"
#include "Avatar.h"
#include "FileReader.h"

FallingSpikeManager::~FallingSpikeManager()
{
	for (FallingSpike* element : m_pItems)
	{
		delete element;
		element = nullptr;
	}
}

void FallingSpikeManager::Initialize(const std::string& filePath)
{
	std::ifstream file{ filePath };

	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string line;
			std::getline(file, line, '>');

			Point2f pos{ FileReader::ToPoint2f(FileReader::GetAttributeValue("Position", line)) };

			AddItem(pos);
		}
	}
}

FallingSpike* FallingSpikeManager::AddItem(const Point2f& bottomLeft)
{
	m_pItems.push_back(new FallingSpike(bottomLeft));
	return m_pItems.back();
}

void FallingSpikeManager::Update(Avatar& playerAvatar, const std::vector<std::vector<Point2f>>& verts)
{
	for (FallingSpike* element : m_pItems)
	{
		element->Update(playerAvatar.GetShape());
	}

	LevelOverlapCheck(verts);
	PlayerOverlapCheck(playerAvatar);
}

void FallingSpikeManager::Draw() const
{
	for (FallingSpike* element : m_pItems)
	{
		element->Draw();
	}
}

void FallingSpikeManager::Reset()
{
	for (FallingSpike* element : m_pItems)
	{
		element->Reset();
	}
}

void FallingSpikeManager::PlayerOverlapCheck(Avatar& playerAvatar) const
{
	for (FallingSpike* element : m_pItems)
	{
		if (element->IsOverlapping(playerAvatar.GetShape()) && !element->IsDestroyed())
		{
			playerAvatar.TakeDamage(1);
			element->Destroy();
		}
	}
}

void FallingSpikeManager::LevelOverlapCheck(const std::vector<std::vector<Point2f>>& verts) const
{
	for (std::vector<Point2f> poly : verts)
	{
		for (FallingSpike* element : m_pItems)
		{
			if (!element->IsDestroyed() && element->IsOverlapping(poly))
			{
				element->Destroy();
			}
		}
	}
}
