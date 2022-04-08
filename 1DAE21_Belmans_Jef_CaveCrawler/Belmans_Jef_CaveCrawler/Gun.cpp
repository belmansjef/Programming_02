#include "Gun.h"
#include "pch.h"

Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::Shoot(const Rectf& actorShape) const
{
	Vector2f relShootPos{ m_ShootPos.x + actorShape.left, m_ShootPos.y + actorShape.bottom };
	std::cout << "Shoot from: " << relShootPos.x << ", " << relShootPos.y << std::endl;
}
