#include "Health.h"
#include "pch.h"

Health::Health(int maxHealth)
	: m_MaxHealth { maxHealth }
	, m_CurrentHealth { maxHealth }
	, m_TimeSinceLastHit{ 0 }
{
}

void Health::Heal(int amount)
{
	m_CurrentHealth = std::min(m_CurrentHealth + amount, m_MaxHealth);
}

void Health::TakeDamage(int amount)
{
	if (m_TimeSinceLastHit + m_DamageCooldown < Time::time)
	{
		m_CurrentHealth -= amount;
		m_TimeSinceLastHit = Time::time;

		std::cout << "Autch!" << std::endl;

		if (m_CurrentHealth <= 0)
		{
			m_CurrentHealth = 0;
			Die();
		}
	}

}

void Health::Die()
{
	std::cout << "Am dead!" << std::endl;
}
