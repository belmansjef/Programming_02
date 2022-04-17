#pragma once
class Health final
{
public:
	Health(int maxHealth, float damageCooldown = 1.0f);
	Health(const Health& other) = delete;
	Health& operator=(const Health& other) = delete;
	Health(Health&& other) = delete;
	Health& operator=(Health&& other) = delete;
	~Health() = default;

	bool GetIsDead() const;

	void Heal(int amount);
	void TakeDamage(int amount);
	bool ShouldHit() const;

private:
	bool m_IsDead;

	int m_MaxHealth;
	int m_CurrentHealth;

	float m_DamageCooldown{ 1.0f };
	float m_TimeSinceLastHit;

	void Die();
};

