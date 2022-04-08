#pragma once
#include <vector>
#include "Vector2f.h"

class Projectile;
class Gun final
{
public:
	explicit Gun();
	Gun(const Gun& other) = delete;
	Gun& operator=(const Gun& other) = delete;
	Gun(Gun&& other) = delete;
	Gun& operator=(Gun&& other) = delete;
	~Gun();

	void Shoot(const Rectf& actorShape) const;

private:
	const Vector2f m_ShootPos{ 18.0f, 8.0f };
};

