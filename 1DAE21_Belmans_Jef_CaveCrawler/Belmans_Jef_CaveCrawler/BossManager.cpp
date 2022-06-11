#include "BossManager.h"
#include "Projectile.h"
#include "Avatar.h"
#include "Enums.h"

BossManager::BossManager(float left, float bottom)
	: m_Boss { left, bottom }
{
}

void BossManager::Reset()
{
	m_Boss.Reset();
}

void BossManager::Update(Avatar& playerAvatar, const Level& level, GameState gameState)
{
	if (gameState != GameState::MainMenu)
	{
		m_Boss.Update(playerAvatar, level);
		PlayerOverlapCheck(playerAvatar);
		ProjectileCollisionCheck(playerAvatar);
	}
}

void BossManager::Draw() const
{
	m_Boss.Draw();
}

void BossManager::PlayerOverlapCheck(Avatar& playerAvatar)
{
	if (m_Boss.IsOverlapping(playerAvatar.GetShape()) && !m_Boss.IsDead())
	{
		playerAvatar.TakeDamage(1);
	}
}

void BossManager::ProjectileCollisionCheck(Avatar& playerAvatar)
{
	for (Projectile* projectile : playerAvatar.GetProjectileManager().GetProjectiles())
	{
		if (!projectile->IsInstanciated() || m_Boss.IsDead()) continue;

		if (projectile->HitCheck(m_Boss.GetBoxCollider()))
		{
			m_Boss.TakeDamage(1);
		}
	}
}
