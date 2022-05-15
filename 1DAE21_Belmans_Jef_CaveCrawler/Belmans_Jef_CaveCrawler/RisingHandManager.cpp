#include <fstream>
#include <sstream>
#include "pch.h"
#include "RisingHandManager.h"
#include "RisingHand.h"
#include "Health.h"
#include "Camera.h"
#include "Projectile.h"
#include "FileReader.h"

RisingHandManager::~RisingHandManager()
{
	for (RisingHand* element : m_pItems)
	{
		delete element;
		element = nullptr;
	}
}

void RisingHandManager::Initialize(const std::string& filePath)
{
	std::ifstream file{ filePath };

	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string line;
			std::getline(file, line, '>');

			int health{ std::stoi(FileReader::GetAttributeValue("Health", line)) };
			Point2f pos{ FileReader::ToPoint2f(FileReader::GetAttributeValue("Position", line)) };

			if (health != 0)
			{
				AddItem(pos, health);
			}
		}
	}
}

RisingHand* RisingHandManager::AddItem(const Point2f& bottomLeft, int maxHealth)
{
	m_pItems.push_back(new RisingHand(bottomLeft, maxHealth));
	return m_pItems.back();
}

void RisingHandManager::Update(const Rectf& actorShape, std::vector<Projectile*> pProjectiles, Health& actorHealth)
{
	for (RisingHand* element : m_pItems)
	{
		if (!element->IsDead())
		{
			element->Update(actorShape);
		}
	}

	PlayerOverlapCheck(actorShape, actorHealth);
	ProjectileCollisionCheck(pProjectiles);
}

void RisingHandManager::Draw() const
{
	for (RisingHand* element : m_pItems)
	{
		if (!element->IsDead())
		{
			element->Draw();
		}
	}
}

void RisingHandManager::Reset()
{
	for (RisingHand* element : m_pItems)
	{
		element->Reset();
	}
}

void RisingHandManager::PlayerOverlapCheck(const Rectf& actorShape, Health& actorHealth) const
{
	for (RisingHand* element : m_pItems)
	{
		if (element->IsOverlapping(actorShape) && !element->IsDead())
		{
			actorHealth.TakeDamage(1);
		}
	}
}

void RisingHandManager::ProjectileCollisionCheck(std::vector<Projectile*> pProjectiles) const
{
	for (Projectile* proj : pProjectiles)
	{
		if (!proj->IsInstanciated()) continue;

		for (RisingHand* element : m_pItems)
		{
			if (!proj->IsInstanciated()) break;
			if (element->IsDead()) continue;

			if (proj->HitCheck(element->GetBoxCollider())) element->TakeDamage(1);
		}
	}
}
