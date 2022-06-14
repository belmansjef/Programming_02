#pragma once
#include <vector>
#include "Health.h"
#include "PhysicsBody.h"
#include "Sprite.h"

class LevelBase;
class ParticleSystem;

class CrabEnemy final
{
public:
	CrabEnemy(float left, float bottom, float width, float height, int movementDirection = 1, int maxHealth = 3);
	~CrabEnemy();

	CrabEnemy(const CrabEnemy& other) = delete;
	CrabEnemy& operator=(const CrabEnemy& other) = delete;
	CrabEnemy(CrabEnemy&& other) = delete;
	CrabEnemy& operator=(CrabEnemy&& other) = delete;

	Rectf GetBoxCollider() const;
	bool IsOverlapping(const Rectf& shape) const;
	bool IsDead() const;

	void TakeDamage(int damage);

	void Update(const LevelBase& level);
	void Draw() const;

	void Reset();

private:
	Sprite m_Sprite;
	Health m_Health;
	PhysicsBody m_PhysicsBody;
	const Point2f m_StartPos;

	ParticleSystem* m_pDeathPS;

	const int m_MaxHealth;
	const float m_MovementSpeed{ 40.0f };
	int m_MovementDirection;

	void DoCollisionCheck(const std::vector<std::vector<Point2f>>& levelVerts);
};

