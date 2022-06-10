#pragma once
#include "Vector2f.h"

class Level;
class PhysicsBody final
{
public:
	PhysicsBody(float left, float bottom, float width, float height, float initialJumpVelocity = 150.0f);
	~PhysicsBody() = default;
	PhysicsBody(const PhysicsBody& other) = delete;
	PhysicsBody& operator=(const PhysicsBody& other) = delete;
	PhysicsBody(PhysicsBody&& other) = delete;
	PhysicsBody& operator=(PhysicsBody&& other) = delete;

	Vector2f& Velocity();
	Rectf& Shape();

	Rectf GetShape() const;
	Point2f GetPosition() const;
	Point2f GetCenter() const;
	float GetTimeSinceGrounded() const;
	bool GetIsGrounded() const;
	bool GetIsMoving() const;

	void SetGravityScale(float gravityScale);
	void SetHasJumped(bool hasJumped);

	void Update(const Level& level);
	void Jump();

private:
	Rectf m_Shape;

	const float m_Gravity{ -350.0f };
	float m_GravityScale{ 1.0f };

	Vector2f m_Velocity{ 0.0f, 0.0f };
	const float m_MaxVelocity{ 700.0f };
	const float m_InitialJumpVelocity{ 150.0f };

	bool m_HasJumped;
	const float m_CoyoteTime{ 0.1f };
	float m_TimeSinceGrounded { 0.0f };

	bool m_IsMoving{ false };
	bool m_IsGrounded { false };

	void ClampVelocity();
};