#include <fstream>
#include <sstream>
#include "CrabEnemyManager.h"
#include "Camera.h"
#include "Projectile.h"
#include "Health.h"
#include "FileReader.h"

CrabEnemyManager::~CrabEnemyManager()
{
	for (CrabEnemy* crab : m_pItems)
	{
		delete crab;
		crab = nullptr;
	}
}

void CrabEnemyManager::Initialize(const std::string& filePath)
{
	std::ifstream file{ filePath };

	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string line;
			std::getline(file, line, '>');

			int health{ std::stoi(FileReader::GetAttributeValue("Health", line)) };
			int direction{ std::stoi(FileReader::GetAttributeValue("Direction", line)) };
			Point2f pos{ FileReader::ToPoint2f(FileReader::GetAttributeValue("Position", line)) };

			if (health != 0)
			{
				AddItem(pos, direction, health);
			}
		}
	}
}

CrabEnemy* CrabEnemyManager::AddItem(const Point2f& bottomLeft, int movementDirection, int maxHealth)
{
	m_pItems.push_back(new CrabEnemy(bottomLeft.x, bottomLeft.y, 24.0f, 11.0f, movementDirection, maxHealth));
	return m_pItems.back();
}

void CrabEnemyManager::Update(const Rectf& actorShape, const Level& level, std::vector<Projectile*> pProjectiles, Health& actorHealth)
{
	for (CrabEnemy* crab : m_pItems)
	{
		crab->Update(level);
	}

	PlayerOverlapCheck(actorShape, actorHealth);
	ProjectileCollisionCheck(pProjectiles);
}

void CrabEnemyManager::Draw() const
{
	for (CrabEnemy* crab : m_pItems)
	{
		if (!crab->IsDead())
		{
			crab->Draw();
		}
	}
}

void CrabEnemyManager::Reset()
{
	for (CrabEnemy* crab : m_pItems)
	{
		crab->Reset();
	}
}

void CrabEnemyManager::PlayerOverlapCheck(const Rectf& actorShape, Health& actorHealth)
{
	for (CrabEnemy* crab : m_pItems)
	{
		if (crab->IsOverlapping(actorShape) && !crab->IsDead())
		{
			actorHealth.TakeDamage(1);
		}
	}
}

void CrabEnemyManager::ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles)
{
	for (Projectile* projectile : pProjectiles)
	{
		if (!projectile->IsInstanciated()) continue;

		for (CrabEnemy* crab : m_pItems)
		{
			if (!projectile->IsInstanciated()) break;
			if (crab->IsDead()) continue;

			if (projectile->HitCheck(crab->GetBoxCollider())) crab->TakeDamage(1);
		}
	}
}
