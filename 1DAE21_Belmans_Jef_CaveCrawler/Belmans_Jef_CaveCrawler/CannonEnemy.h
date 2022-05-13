#pragma once
#include "Health.h"
#include "structs.h"
#include "Sprite.h"
#include "ProjectileManager.h"

class Health;
class CannonEnemy final
{
public:
	CannonEnemy(const Point2f& bottomLeft, float orientation);

	void Update(const Rectf& actorShape, Health& actorHealth, const std::vector<std::vector<Point2f>>& levelVerts);
	void Draw() const;

private:
	Sprite m_SpriteBase;
	Sprite m_SpriteBarrel;
	Rectf m_BoxCollider;
	Health m_Health;
	ProjectileManager m_ProjectileManager;

	const float m_ShotCooldown;
	float m_LastShotTime;

	Point2f m_BaseCenter;
	float m_BaseOrientation;
	float m_BarrelAngle;

	void Shoot(const Vector2f& freeVec);
};