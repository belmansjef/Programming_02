#include <fstream>
#include <sstream>
#include "CannonEnemyManager.h"
#include "LevelBase.h"
#include "Projectile.h"
#include "Avatar.h"
#include "FileReader.h"
#include "Enums.h"

CannonEnemyManager::~CannonEnemyManager()
{
	for (CannonEnemy* element : m_pItems)
	{
		delete element;
		element = nullptr;
	}
}

void CannonEnemyManager::Initialize(const std::string& filePath)
{
	std::ifstream file{ filePath };

	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string line;
			std::getline(file, line, '>');

			Point2f pos{ FileReader::ToPoint2f(FileReader::GetAttributeValue("Position", line)) };
			int orientation{ std::stoi(FileReader::GetAttributeValue("Orientation", line)) };

			AddItem(pos, CannonOrientation(orientation));
		}
	}
}

CannonEnemy* CannonEnemyManager::AddItem(const Point2f& bottomLeft, const CannonOrientation& orientation)
{
	m_pItems.push_back(new CannonEnemy(bottomLeft, orientation));
	return m_pItems.back();
}

void CannonEnemyManager::Update(Avatar& playerAvatar, const std::vector<std::vector<Point2f>>& levelVerts, std::vector<Projectile*> pProjectiles)
{
	for (CannonEnemy* element : m_pItems)
	{
		element->Update(playerAvatar, levelVerts);
	}

	ProjectileCollisionCheck(pProjectiles);
}

void CannonEnemyManager::Draw() const
{
	for (CannonEnemy* element : m_pItems)
	{
		element->Draw();
	}
}

void CannonEnemyManager::Reset()
{
	for (CannonEnemy* element : m_pItems)
	{
		element->Reset();
	}
}

void CannonEnemyManager::ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles)
{
	for (Projectile* projectile : pProjectiles)
	{
		if (!projectile->IsInstanciated()) continue;

		for (CannonEnemy* cannon : m_pItems)
		{
			if (cannon->IsDead()) continue;
			if (!projectile->IsInstanciated()) break;

			if (projectile->HitCheck(cannon->GetBoxCollider())) cannon->TakeDamage(1);
		}
	}
}
