#pragma once

class Sprite;
class Health final
{
public:
	Health(int maxHealth, Sprite* sprite, float damageCooldown = 1.0f, bool isPlayer = false);
	Health(const Health& other) = delete;
	Health& operator=(const Health& other) = delete;
	Health(Health&& other) = delete;
	Health& operator=(Health&& other) = delete;
	~Health() = default;

	bool GetIsDead() const;
	int GetCurrentHealth() const;

	void Heal(int amount);
	void TakeDamage(int amount);
	bool ShouldHit() const;

private:
	Sprite* m_pSprite;
	bool m_IsDead;
	bool m_IsPlayer;

	int m_MaxHealth;
	int m_CurrentHealth;

	float m_DamageCooldown;
	float m_TimeSinceLastHit;

	void Die();
};

