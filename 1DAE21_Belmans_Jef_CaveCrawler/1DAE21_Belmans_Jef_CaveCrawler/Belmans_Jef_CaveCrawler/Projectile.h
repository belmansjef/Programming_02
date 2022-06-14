#pragma once
#include <vector>
#include "Vector2f.h"

enum class ProjectileType;
class Texture;
class ParticleSystem;

class Projectile final
{
public:
	Projectile(ProjectileType type);
	Projectile(const Vector2f& velocity, const Rectf& boxCollider);
	~Projectile();

	Projectile(const Projectile& other) = delete;
	Projectile& operator=(const Projectile& other) = delete;
	Projectile(Projectile&& other) = delete;
	Projectile& operator=(Projectile&& other) = delete;

	void Instanciate(const Vector2f& velocity, const Point2f& bottomLeft);
	bool IsInstanciated() const;
	bool IsEmittingParticles() const;

	void Update();
	void Draw() const;

	void Reset();

	bool HitCheck(const std::vector<Point2f>& verts);
	bool HitCheck(const Rectf& rect);
private:
	bool m_IsInstanciated;

	Texture* m_pTexture;
	Rectf m_BoxCollider;
	Rayf m_Ray;

	ParticleSystem* m_pHitPS;

	Vector2f m_Velocity;
	float m_AngleRad;
	float m_AngleDeg;
};

