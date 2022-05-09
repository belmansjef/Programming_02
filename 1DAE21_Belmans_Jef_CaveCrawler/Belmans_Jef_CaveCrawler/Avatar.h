#pragma once
#include <math.h>
#include "utils.h"
#include "Sprite.h"
#include "Health.h"
#include "Gun.h"
#include "PhysicsBody.h"
#include "pch.h"

class Level;
class Avatar final
{
public:
	Avatar(float left, float bottom, float width, float height);
	Avatar(const Avatar& other) = delete;
	Avatar& operator=(const Avatar& other) = delete;
	Avatar(Avatar&& other) = delete;
	Avatar& operator=(Avatar&& other) = delete;
	~Avatar() = default;

	void TakeDamage(int damage = 1);
	void Heal(int value = 1);

	bool ShouldTrack();
	bool GetIsDead() const;
	Rectf GetShape() const;
	Health& GetHealth();
	ProjectileManager& GetProjectileManager();

	void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
	void Update(const Level& level);
	void Draw() const;
	void Reset();

private:
	Point2f m_StartPos;
	Sprite m_Sprite;
	PhysicsBody m_PhysicsBody;
	Gun m_Gun;

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
	void ProcessInput(const Level& level);

	void SetAnimation();
	void SetGravityScale();
};