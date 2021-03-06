#pragma once
#include <math.h>
#include "pch.h"
#include "utils.h"
#include "Sprite.h"
#include "Health.h"
#include "PhysicsBody.h"
#include "Gun.h"

enum class GameState;
class LevelBase;
class ParticleSystem;

class Avatar final
{
public:
	Avatar(float left, float bottom, float width, float height);
	~Avatar();

	Avatar(const Avatar& other) = delete;
	Avatar& operator=(const Avatar& other) = delete;
	Avatar(Avatar&& other) = delete;
	Avatar& operator=(Avatar&& other) = delete;

	void TakeDamage(int damage = 1);
	void Heal(int value = 1);

	bool ShouldTrack();
	bool GetIsDead() const;
	Rectf GetShape() const;
	Rectf& Shape();
	Health& GetHealth();
	ProjectileManager& GetProjectileManager();

	void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
	void Update(const LevelBase& level, const GameState& state);
	void Draw() const;
	void Reset();

private:
	Point2f m_StartPos;
	Sprite m_Sprite;
	PhysicsBody m_PhysicsBody;
	Gun m_Gun;

	ParticleSystem* m_pDeathPS;

	const int m_MaxHealth{ 4 };
	Health m_AvatarHealth;

	bool m_ShouldTrack{ false };
	const float m_HorCamDeadZone{ 10.0f };
	const float m_VerCamDeadZone{ 10.0f };

	const float m_StandStillDetectionTime{ 1.0f };
	float m_TimeSinceLastMoved{ 0.0f };
	Point2f m_StandStillPos{ 0.0f, 0.0f };

	const float m_MovementSpeed{ 80.0f };

	GLfloat m_HorizontalScale{ 1 };
	int m_MovementDirection{ 0 };
	bool m_IsPressingJump{ false };
	bool m_IsPressingShoot{ false };

	void GetInput();
	void ProcessInput(const LevelBase& level);

	void SetAnimation();
	void SetGravityScale();
};