#pragma once
#include <vector>
#include "Vector2f.h"

class Texture;

class Projectile final
{
public:
	Projectile();
	Projectile(const Vector2f& velocity, const Rectf& boxCollider);
	~Projectile();
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
	bool m_IsInstanciated;
	Texture* m_pTexture;
	Rectf m_BoxCollider;

	Vector2f m_Velocity;
	float m_AngleRad;
	float m_AngleDeg;
};

