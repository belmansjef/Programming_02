#pragma once
#include "Health.h"
#include "structs.h"
#include "Sprite.h"

class CannonEnemy final
{
public:
	CannonEnemy(const Point2f& bottomLeft, float orientation);

	void Update(const Rectf& actorShape);
	void Draw() const;

private:
	Sprite m_SpriteBase;
	Sprite m_SpriteBarrel;
	Rectf m_BoxCollider;
	Health m_Health;
	float m_BaseOrientation;
	float m_BarrelAngle;
};

