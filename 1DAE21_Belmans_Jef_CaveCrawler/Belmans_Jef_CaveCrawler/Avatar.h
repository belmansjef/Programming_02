#pragma once
#include <math.h>
#include "utils.h"
#include "Texture.h"
#include "Sprite.h"
#include "Health.h"
#include "Gun.h"

class Level;
class Avatar
{
public:
	Avatar(float left, float bottom, float width, float height, int maxhealth);
	Avatar(const Avatar& other) = delete;
	Avatar& operator=(const Avatar& other) = delete;
	Avatar(Avatar&& other) = delete;
	Avatar& operator=(Avatar&& other) = delete;
	virtual ~Avatar() = default;

	void Update(const Level& level);
	void Draw() const;

	bool ShouldTrack() const;

	Rectf GetShape() const;
	Health& GetHealth();

private:
	Sprite m_Sprite;
	Rectf m_Shape;
	Health m_AvatarHealth;

	float m_Gravity{ -350.0f };
	float m_GravityScale{ 1.0f };

	Vector2f m_Velocity{ 0.0f, 0.0f };
	float m_MaxVelocity{ 700.0f };
	float m_Damping{ 1.0f };

	const float m_HorCamDeadZone{ 10.0f };
	const float m_VerCamDeadZone{ 10.0f };

	bool m_IsMoving{ false };
	const float m_StandStillDetectionTime{ 0.75f };
	float m_TimeSinceMovement{ 0.0f };
	Point2f m_StandStillPos{ 0.0f, 0.0f };

	GLfloat m_HorizontalScale{ 1 };
	int m_MovementDirection{ 0 };
	bool m_IsPressingJump{ false };
	bool m_IsPressingShoot{ false };

	bool m_IsGrounded{ false };
	bool m_HasJumped{ false };
	float m_MovementSpeed{ 80.0f };
	float m_JumpHeight{ 5.0f };
	float m_InitialJumpVelocity{ 175.0f };
	float m_TimeSinceGrounded{ 0.0f };
	const float m_CoyoteTime{ 0.1f };

	Gun m_Gun;

	void GetInput();
	void ProcessInput(const Level& level);

	void Jump();
	void SetAnimation();
	void SetGravityScale();

	void ClampVelocity();
	void DampVelocity();
};