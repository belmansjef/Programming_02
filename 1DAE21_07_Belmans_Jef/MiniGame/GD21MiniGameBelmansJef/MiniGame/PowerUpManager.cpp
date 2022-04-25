#include "pch.h"
#include "PowerUpManager.h"
#include "PowerUp.h"
#include "SoundEffect.h"

PowerUpManager::PowerUpManager()
	: m_pPowerUpSE{ new SoundEffect("Resources/Sounds/powerUp.mp3")}
{
}

PowerUpManager::~PowerUpManager()
{
	for (PowerUp* element : m_pItems)
	{
		DeletePowerUp(element);
	}

	delete m_pPowerUpSE;
	m_pPowerUpSE = nullptr;
}

PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
	m_pItems.push_back(new PowerUp(center, type));
	return m_pItems.back();
}

void PowerUpManager::Update(float elapsedSec)
{
	for (PowerUp* element : m_pItems)
	{
		element->Update(elapsedSec);
	}
}

void PowerUpManager::Draw() const
{
	for (PowerUp* element : m_pItems)
	{
		element->Draw();
	}
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
	for (int i = 0; i < m_pItems.size(); i++)
	{
		if (m_pItems[i]->IsOverlapping(rect))
		{
			DeletePowerUp(m_pItems[i]);

			PowerUp* temp = m_pItems.back();
			m_pItems[i] = temp;
			m_pItems.pop_back();
			
			m_pPowerUpSE->Play(1);

			return true;
		}
	}

	return false;
}

void PowerUpManager::DeletePowerUp(const PowerUp* powerup)
{
	delete powerup;
	powerup = nullptr;
}
