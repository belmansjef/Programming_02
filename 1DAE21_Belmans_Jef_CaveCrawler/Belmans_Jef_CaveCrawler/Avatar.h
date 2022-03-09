#pragma once
#include <math.h>
#include "utils.h"
#include "Texture.h"
#include "Sprite.h"

enum class ActionState
{
	idle,
	moving,
	jumping
};

class Level;

class Avatar
{
public:
	Avatar();
	~Avatar();

	void Update(float elapsedSec, const Level& level);
	void Draw() const;
	void PowerUpHit();
	Rectf GetShape() const;

private:
	Sprite m_Sprite;
	Rectf m_Shape{ 50.0f, 280.0f, 24.0f, 16.0f };

	float m_Gravity{ -981.0f };
	float m_GravityScale{ 1.0f };
	float m_Damping{ 1.0f };
	Vector2f m_Velocity{ 0.0f, 0.0f };
	float m_MaxVelocity{ 700.0f };

	float m_MovementSpeed{ 200.0f };
	float m_JumpHeight{ 5.0f };
	float m_InitialJumpVelocity{ 542.5f };

	ActionState m_ActionState{ ActionState::moving };

	void UpdateIdleState();
	void UpdateMovingState(float elapsedSec, const Level& level);
	void UpdateJumpingState(float elapsedSec, const Level& level);
	void ClampVelocity();
	void DampVelocity(float elapsedSec);
};

