#include <fstream>
#include <sstream>
#include "CrabEnemyManager.h"
#include "Camera.h"
#include "Projectile.h"
#include "Avatar.h"
#include "Health.h"
#include "FileReader.h"
#include "ScoreManager.h"

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

void CrabEnemyManager::Update(Avatar& playerAvatar, const LevelBase& level, std::vector<Projectile*> pProjectiles, ScoreManager& scoreManager)
{
	for (CrabEnemy* crab : m_pItems)
	{
		crab->Update(level);
	}

	PlayerOverlapCheck(playerAvatar);
	ProjectileCollisionCheck(pProjectiles, scoreManager);
}

void CrabEnemyManager::Draw() const
{
	for (CrabEnemy* crab : m_pItems)
	{
		crab->Draw();
	}
}

void CrabEnemyManager::Reset()
{
	for (CrabEnemy* crab : m_pItems)
	{
		crab->Reset();
	}
}

void CrabEnemyManager::PlayerOverlapCheck(Avatar& playerAvatar)
{
	for (CrabEnemy* crab : m_pItems)
	{
		if (crab->IsOverlapping(playerAvatar.GetShape()) && !crab->IsDead())
		{
			playerAvatar.TakeDamage(1);
		}
	}
}

void CrabEnemyManager::ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles, ScoreManager& scoreManager)
{
	for (Projectile* projectile : pProjectiles)
	{
		if (!projectile->IsInstanciated()) continue;

		for (CrabEnemy* crab : m_pItems)
		{
			if (!projectile->IsInstanciated()) break;
			if (crab->IsDead()) continue;

			if (projectile->HitCheck(crab->GetBoxCollider())) 
			{
				crab->TakeDamage(1);
				if (crab->IsDead())
				{
					scoreManager.AddScore(150);
				}
			}
		}
	}
}
