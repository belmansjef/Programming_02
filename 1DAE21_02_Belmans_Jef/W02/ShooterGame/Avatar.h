#pragma once
#include "pch.h"
#include "Bullet.h"

class Enemy;
class Bullet;
class Avatar
{
public:
	Avatar();
	Avatar(const Point2f& center, float width, float height, const Rectf& boundaries);
	~Avatar();

	void Update(float elapsedSec, Enemy* pEnemies, int numEnemies);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void Draw() const;
	void SetCenter(const Point2f& center);
	void SetDimensions(float width, float height);
	void SetBoundaries(const Rectf& boundaries);

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	Rectf m_PlayerRect;
	float m_Speed;
	Rectf m_Boundaries;

	Bullet m_Bullet;
	void ShootBullet();

	void HandleMoveKeysState(float elapsedSec);
	void Clamp();
};

