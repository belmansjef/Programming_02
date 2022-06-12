#include "BossManager.h"
#include "Projectile.h"
#include "Avatar.h"
#include "SoundManager.h"
#include "Enums.h"

BossManager::BossManager(float left, float bottom, const Window& window)
	: m_IsPlayerInBossRoom { false }
	, m_Boss { left, bottom }
	, m_BossRoom { 290.0f, 16.0f, 242.0f, 216.0f }
	, m_HealthBarFill { window.width / 2.0f - 128.0f, window.height - 128.0f, m_HealthBarBaseWidth, 56.0f }
	, m_HealthBarBorder { window.width / 2.0f - 130.0f, window.height - 130.0f, m_HealthBarBaseWidth + 4.0f, 60.0f }
{
}

void BossManager::Reset()
{
	m_Boss.Reset();
	m_IsPlayerInBossRoom = false;
	m_HealthBarFill.width = m_HealthBarBaseWidth;
}

void BossManager::Update(Avatar& playerAvatar, const LevelBase& level, GameState gameState)
{
	if (gameState != GameState::MainMenu && m_IsPlayerInBossRoom)
	{
		m_Boss.Update(playerAvatar, level);
		PlayerOverlapCheck(playerAvatar);
		ProjectileCollisionCheck(playerAvatar);
	}

	if (utils::IsOverlapping(playerAvatar.GetShape(), m_BossRoom) && !m_IsPlayerInBossRoom)
	{
		SoundManager::GetInstance()->StopMainSoundtrack();
		SoundManager::GetInstance()->PlayBossSoundtrack();
		m_IsPlayerInBossRoom = true;
	}
	else if (!utils::IsOverlapping(playerAvatar.GetShape(), m_BossRoom) && m_IsPlayerInBossRoom)
	{
		SoundManager::GetInstance()->StopBossSoundtrack();
		SoundManager::GetInstance()->PlayMainSoundtrack();
		m_IsPlayerInBossRoom = false;
	}
}

void BossManager::Draw() const
{
	m_Boss.Draw();
}

void BossManager::DrawHUD() const
{
	if (m_IsPlayerInBossRoom && !m_Boss.IsDead())
	{
		utils::SetColor(Color4f(1.0f, 1.0f, 1.0f, 1.0f));
		utils::DrawRect(m_HealthBarBorder, 4.0f);
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
		utils::FillRect(m_HealthBarFill);
	}
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
			m_HealthBarFill.width = (m_HealthBarBaseWidth / m_Boss.GetMaxHealth()) * m_Boss.GetHealth();
		}
	}
}
