#pragma once
#include "Sprite.h"
#include "Health.h"

class RisingHand final
{
public:
	RisingHand(const Point2f& bottomLeft, int maxHealth);
	~RisingHand() = default;
	RisingHand(const RisingHand& other) = delete;
	RisingHand& operator=(const RisingHand& other) = delete;
	RisingHand(RisingHand&& other) = delete;
	RisingHand& operator=(RisingHand&& other) = delete;

	Rectf GetBoxCollider() const;
	Health& GetHealth();

	void Update(const Rectf& actorShape);
	void Draw() const;

	void Reset();

	bool IsOverlapping(const Rectf& actorShape) const;

private:
	const float m_TriggerDistance{ 48.0f };

	Sprite m_Sprite;
	Rectf m_BoxCollider;
	Health m_Health;
};

