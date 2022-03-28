#include <iostream>
#include "pch.h"
#include "CollectibleManager.h"
#include "Collectible.h"

CollectibleManager::CollectibleManager()
{

}

CollectibleManager::~CollectibleManager()
{
	for (Collectible* element : m_pItems)
	{
		DeletePowerUp(element);
	}
}

Collectible* CollectibleManager::AddItem(const Point2f& center, Collectible::Type type)
{
	m_pItems.push_back(new Collectible(center, type));
	return m_pItems.back();
}

void CollectibleManager::Draw() const
{
	for (Collectible* element : m_pItems)
	{
		element->Draw();
	}
}

size_t CollectibleManager::Size() const
{
	return m_pItems.size();
}

bool CollectibleManager::HitItem(const Rectf& rect)
{
	for (int i = 0; i < m_pItems.size(); i++)
	{
		if (m_pItems[i]->IsOverlapping(rect))
		{
			DeletePowerUp(m_pItems[i]);

			Collectible* temp = m_pItems.back();
			m_pItems[i] = temp;
			m_pItems.pop_back();
			
			return true;
		}
	}

	return false;
}

void CollectibleManager::DeletePowerUp(const Collectible* powerup) const
{
	delete powerup;
	powerup = nullptr;
}
