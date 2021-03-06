#include "BossManager.h"
#include "Projectile.h"
#include "Avatar.h"
#include "SoundManager.h"
#include "Enums.h"
#include "ScoreManager.h"

BossManager::BossManager(float left, float bottom, const Window& window)
	: m_IsPlayerInBossRoom { false }
	, m_Boss { left, bottom }
	, m_BossRoom { 290.0f, 16.0f, 242.0f, 216.0f }
	, m_HealthBarFill { window.width / 2.0f - 128.0f, window.height - 128.0f, m_HealthBarBaseWidth, 56.0f }
	, m_HealthBarBorder { window.width / 2.0f - 130.0f, window.height - 130.0f, m_HealthBarBaseWidth + 4.0f, 60.0f }
	, m_DoorLeft { 258.0f, 32.0f, 24.0f, 24.0f }
	, m_DoorRight{ 520.0f, 32.0f, 24.0f, 24.0f}
{
}

void BossManager::Reset()
{
	m_Boss.Reset();
	m_IsPlayerInBossRoom = false;
	m_HealthBarFill.width = m_HealthBarBaseWidth;
	SoundManager::GetInstance()->PlayMainSoundtrack();
}

void BossManager::Update(Avatar& playerAvatar, const LevelBase& level, GameState gameState, ScoreManager& scoreManager)
{
	if (gameState != GameState::MainMenu && m_IsPlayerInBossRoom)
	{
		m_Boss.Update(playerAvatar, level);
		PlayerOverlapCheck(playerAvatar);
		ProjectileCollisionCheck(playerAvatar, scoreManager);
		DoorCollisionCheck(playerAvatar);
	}

	if (utils::IsOverlapping(playerAvatar.GetShape(), m_BossRoom) && !m_IsPlayerInBossRoom)
	{
		SoundManager::GetInstance()->PlayBossSoundtrack();
		
		m_IsPlayerInBossRoom = true;
		m_Boss.PlayerEnteredRoom();
	}
	else if (!utils::IsOverlapping(playerAvatar.GetShape(), m_BossRoom) && m_IsPlayerInBossRoom)
	{
		SoundManager::GetInstance()->PlayMainSoundtrack();
		m_IsPlayerInBossRoom = false;
	}
}

void BossManager::Draw() const
{
	m_Boss.Draw();
	if (m_IsPlayerInBossRoom && !m_Boss.IsDead())
	{
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
		utils::FillRect(m_DoorLeft);
		utils::FillRect(m_DoorRight);
	}
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

void BossManager::DoorCollisionCheck(Avatar& playerAvatar)
{
	if (m_IsPlayerInBossRoom && !m_Boss.IsDead())
	{
		Rectf& actorShape{ playerAvatar.Shape() };
		if (utils::IsOverlapping(actorShape, m_DoorLeft))
		{
			actorShape.left = m_DoorLeft.left + m_DoorLeft.width;
		}

		if (utils::IsOverlapping(actorShape, m_DoorRight))
		{
			actorShape.left = m_DoorRight.left - actorShape.width;
		}
	}
}

void BossManager::PlayerOverlapCheck(Avatar& playerAvatar)
{
	if (m_Boss.IsOverlapping(playerAvatar.GetShape()) && !m_Boss.IsDead())
	{
		playerAvatar.TakeDamage(1);
	}
}

void BossManager::ProjectileCollisionCheck(Avatar& playerAvatar, ScoreManager& scoreManager)
{
	for (Projectile* projectile : playerAvatar.GetProjectileManager().GetProjectiles())
	{
		if (!projectile->IsInstanciated() || m_Boss.IsDead()) continue;

		if (projectile->HitCheck(m_Boss.GetBoxCollider()))
		{
			m_Boss.TakeDamage(1);
			m_HealthBarFill.width = (m_HealthBarBaseWidth / m_Boss.GetMaxHealth()) * m_Boss.GetHealth();
			if (m_Boss.IsDead())
			{
				scoreManager.AddScore(1250);
			}
		}
	}
}
