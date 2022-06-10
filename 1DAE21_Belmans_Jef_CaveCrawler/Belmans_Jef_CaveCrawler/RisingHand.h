#pragma once
#include "Sprite.h"
#include "Health.h"

class ParticleSystem;

class RisingHand final
{
public:
	RisingHand(const Point2f& bottomLeft, int maxHealth = 3);
	~RisingHand() = default;
	RisingHand(const RisingHand& other) = delete;
	RisingHand& operator=(const RisingHand& other) = delete;
	RisingHand(RisingHand&& other) = delete;
	RisingHand& operator=(RisingHand&& other) = delete;

	Rectf GetBoxCollider() const;
	bool IsDead() const;
	bool IsOverlapping(const Rectf& actorShape) const;
	void TakeDamage(int damage);

	void Update(const Rectf& actorShape);
	void Draw() const;
	void Reset();

private:
	const float m_TriggerDistance{ 48.0f };
	const float m_HorDrawOffset{ 4.0f };

	ParticleSystem* m_pDeathPS;

	const int m_MaxHealth;
	Sprite m_Sprite;
	Rectf m_BoxCollider;
	Health m_Health;

	bool m_HasExtended{ false };
};

