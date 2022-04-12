#include "Health.h"
#include "pch.h"

Health::Health(int maxHealth, float damageCooldown)
	: m_MaxHealth { maxHealth }
	, m_CurrentHealth { maxHealth }
	, m_TimeSinceLastHit{ -damageCooldown }
	, m_DamageCooldown { damageCooldown }
	, m_IsDead { false } 
{
}

bool Health::GetIsDead() const
{
	return m_IsDead;
}

void Health::Heal(int amount)
{
	m_CurrentHealth = std::min(m_CurrentHealth + amount, m_MaxHealth);
}

void Health::TakeDamage(int amount)
{
	if (ShouldHit())
	{
		m_CurrentHealth -= amount;
		m_TimeSinceLastHit = Time::time;

		if (m_CurrentHealth <= 0)
		{
			m_CurrentHealth = 0;
			Die();
		}
		else
		{
			// Took damage
		}
	}
}

bool Health::ShouldHit() const
{
	return m_TimeSinceLastHit + m_DamageCooldown <= Time::time;
}

void Health::Die()
{
	m_IsDead = true;
}
