#include "Health.h"
#include "pch.h"

Health::Health(int maxHealth)
	: m_MaxHealth { maxHealth }
	, m_CurrentHealth { maxHealth }
{
}

void Health::Heal(int amount)
{
	m_CurrentHealth = std::min(m_CurrentHealth + amount, m_MaxHealth);
}

void Health::TakeDamage(int amount)
{
	m_CurrentHealth -= amount;
	if (m_CurrentHealth <= 0)
	{
		m_CurrentHealth = 0;
		Die();
	}
}

void Health::Die()
{
	std::cout << "Am dead!" << std::endl;
}
