#pragma once
#include <vector>
#include "Vector2f.h"
#include "ProjectileManager.h"

class Gun final
{
public:
	explicit Gun();
	~Gun();
	Gun(const Gun& other) = delete;
	Gun& operator=(const Gun& other) = delete;
	Gun(Gun&& other) = delete;
	Gun& operator=(Gun&& other) = delete;

	ProjectileManager& GetProjectileManager();

	void Shoot(const Rectf& actorShape, int horScale);

	void Update(const std::vector<std::vector<Point2f>>& levelVerts);
	void Draw() const;

private:
	ProjectileManager m_ProjectileManager;

	const Vector2f m_ShootPos{ 17.0f, 7.0f };
	const float m_ShotSpeed{ 150.0f };
	const float m_FireRate{ 0.35f };
	float m_LastShotTime{ 0.0f };
};

