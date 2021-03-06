#include "Health.h"
#include "pch.h"
#include "HUD.h"
#include "Sprite.h"
#include "Enums.h"
#include "Camera.h"
#include "SoundManager.h"
#include "ParticleSystem.h"

Health::Health()
	: Health(3, nullptr)
{
}

Health::Health(int maxHealth, Sprite* sprite, float damageCooldown, bool isPlayer)
	: m_MaxHealth { maxHealth }
	, m_CurrentHealth { maxHealth }
	, m_TimeSinceLastHit{ -damageCooldown }
	, m_DamageCooldown { damageCooldown }
	, m_IsDead { false } 
	, m_IsPlayer { isPlayer }
	, m_pSprite { sprite }
{
}

bool Health::GetIsDead() const
{
	return m_IsDead;
}

int Health::GetCurrentHealth() const
{
	return m_CurrentHealth;
}

void Health::Heal(int amount)
{
	m_CurrentHealth = std::min(m_CurrentHealth + amount, m_MaxHealth);
	m_IsDead = m_CurrentHealth == 0;

	if (m_IsPlayer)
	{
		HUD::UpdateHealth(m_CurrentHealth);
		SoundManager::GetInstance()->PlaySound(SoundType::healthPickup);
	}
}

void Health::TakeDamage(int amount)
{
	if (ShouldHit())
	{
		m_CurrentHealth -= amount;
		m_TimeSinceLastHit = Time::GetInstance()->m_Time;
		SoundManager::GetInstance()->PlaySound(SoundType::hitHurt);

		if (m_CurrentHealth <= 0 && !m_IsDead)
		{
			if (m_IsPlayer)
			{
				HUD::UpdateHealth(m_CurrentHealth);
			}
			m_CurrentHealth = 0;
			Die();
		}
		else if(m_IsPlayer)
		{
			HUD::UpdateHealth(m_CurrentHealth);
			Camera::DoScreenShake();
			m_pSprite->FlashSprite();
		}
		else
		{
			m_pSprite->FlashSprite();
		}
	}
}

bool Health::ShouldHit() const
{
	return m_TimeSinceLastHit + m_DamageCooldown <= Time::GetInstance()->m_Time;
}

void Health::Die()
{
	m_IsDead = true;
	SoundManager::GetInstance()->PlaySound(SoundType::explosion);
}