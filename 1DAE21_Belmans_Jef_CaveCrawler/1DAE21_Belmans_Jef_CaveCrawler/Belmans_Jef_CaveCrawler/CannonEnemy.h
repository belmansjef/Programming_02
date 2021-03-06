#pragma once
#include "Health.h"
#include "structs.h"
#include "Sprite.h"
#include "ProjectileManager.h"

enum class CannonOrientation;
class Health;
class Avatar;
class ParticleSystem;

class CannonEnemy final
{
public:
	CannonEnemy(const Point2f& bottomLeft, const CannonOrientation& orientation);
	~CannonEnemy();

	CannonEnemy(const CannonEnemy& other) = delete;
	CannonEnemy& operator=(const CannonEnemy& other) = delete;
	CannonEnemy(CannonEnemy&& other) = delete;
	CannonEnemy& operator=(CannonEnemy&& other) = delete;

	void Update(Avatar& playerAvatar, const std::vector<std::vector<Point2f>>& levelVerts);
	void Draw() const;
	void Reset();

	void TakeDamage(int damage = 1);

	Rectf GetBoxCollider() const;
	bool IsOverlapping(const Rectf& shape) const;
	bool IsDead() const;

private:
	Sprite m_SpriteBase;
	Sprite m_SpriteBarrel;
	Rectf m_BoxCollider;
	Health m_Health;
	ProjectileManager m_ProjectileManager;
	ParticleSystem* m_pDeathPS;

	const float m_ShotCooldown;
	float m_LastShotTime;

	Point2f m_BaseCenter;
	float m_BaseOrientation;
	float m_BarrelAngle;

	bool m_IsPlayerInRange;
	const float m_Range;
	
	void DrawBarrel() const;
	void DrawBase() const;
	void SetAnimation();
	void UpdateProjectiles(Avatar& playerAvatar, const std::vector<std::vector<Point2f>>& levelVerts);
	void Shoot(const Vector2f& freeVec);
};