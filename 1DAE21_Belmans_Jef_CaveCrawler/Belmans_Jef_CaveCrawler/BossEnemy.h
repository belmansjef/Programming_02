#pragma once
#include "Sprite.h"
#include "PhysicsBody.h"
#include "Health.h"
#include "ProjectileManager.h"

enum class BossState;
class LevelBase;
class Avatar;
class ParticleSystem;

class BossEnemy final
{
public:
	BossEnemy(float left, float bottom);
	~BossEnemy();

	BossEnemy(const BossEnemy& other) = delete;
	BossEnemy& operator=(const BossEnemy& other) = delete;
	BossEnemy(BossEnemy&& other) = delete;
	BossEnemy& operator=(BossEnemy&& other) = delete;

	bool IsOverlapping(const Rectf& otherShape) const;
	bool IsDead() const;
	int GetHealth() const;
	int GetMaxHealth() const;
	Rectf GetBoxCollider() const;

	void TakeDamage(int damage);

	void Reset();
	void Update(Avatar& playerAvatar, const LevelBase& level);
	void Draw() const;

private:
	Point2f m_StartPos;
	Sprite m_SpriteBody;
	Sprite m_SpriteBarrel;
	PhysicsBody m_PhysicsBody;
	ProjectileManager m_ProjectileManager;
	ParticleSystem* m_pDeathPS;

	BossState m_CurrentState;

	const int m_MaxHealth{ 10 };
	Health m_Health;

	const float m_HorizontalMovementSpeed{ 50.0f };
	int m_MovementDirection;

	const float m_ShotCooldown;
	float m_LastShotTime;

	float m_BarrelAngle;

	// Animation
	const float m_StandTime{ 1.5f };
	const float m_PreChargeTime{ 0.5f };
	const float m_ChargeTime{ 0.25f };
	float m_TimeSinceGrounded;

	void SetState();
	void DrawBarrel() const;
	void Shoot(const Vector2f& freeVec);
	void UpdateProjectiles(Avatar& playerAvatar, const std::vector<std::vector<Point2f>>& levelVerts);
};

