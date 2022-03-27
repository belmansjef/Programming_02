#pragma once
class Health final
{
public:
	explicit Health(int maxHealth);
	Health(const Health& other) = delete;
	Health& operator=(const Health& other) = delete;
	Health(Health&& other) = delete;
	Health& operator=(Health&& other) = delete;
	~Health() = default;

	void Heal(int amount);
	void TakeDamage(int amount);

private:
	int m_MaxHealth;
	int m_CurrentHealth;

	void Die();
};

