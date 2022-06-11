#pragma once
#include "Sprite.h"
#include "PhysicsBody.h"
#include "Health.h"

enum class BossState;
class Level;
class Avatar;

class BossEnemy final
{
public:
	BossEnemy(float left, float bottom);
	~BossEnemy() = default;

	void Update(const Level& level, const Avatar& playerAvatar);
	void Draw() const;

private:
	Point2f m_StartPos;
	Sprite m_Sprite;
	PhysicsBody m_PhysicsBody;

	BossState m_CurrentState;

	const int m_MaxHealth{ 10 };
	Health m_Health;

	const float m_HorizontalMovementSpeed{ 50.0f };
	int m_MovementDirection;

	// Animation
	const float m_StandTime{ 1.5f };
	const float m_PreChargeTime{ 0.5f };
	const float m_ChargeTime{ 0.25f };
	float m_TimeSinceGrounded;

	void SetState();
};

