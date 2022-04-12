#pragma once
#include <vector>
#include "Vector2f.h"

class Projectile final
{
public:
	Projectile();
	~Projectile() = default;
	Projectile(Vector2f velocity, Rectf rectGraphic);
	Projectile(const Projectile& other) = delete;
	Projectile& operator=(const Projectile& other) = delete;
	Projectile(Projectile&& other) = delete;
	Projectile& operator=(Projectile&& other) = delete;

	void Instanciate(const Vector2f& velocity, const Point2f& bottomLeft);
	bool IsInstanciated() const;

	void Update();
	void Draw() const;

	void Reset();

	bool HitCheck(const std::vector<Point2f>& verts);
	bool HitCheck(const Rectf& rect);
private:
	bool m_IsInstanciated{};

	Rectf m_RectGraphic{};
	Circlef m_CircleCollider{};
	
	Vector2f m_Velocity{};
	float m_Angle{};
};

