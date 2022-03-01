#pragma once
#include "utils.h"

class Level;

enum class ActionState
{
	waiting,
	moving,
	transforming
};

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
	Rectf m_Shape{ 50.0f, 280.0f, 36.0f, 97.0f };
	float m_HorSpeed{ 200.0f };
	float m_JumpSpeed{ 600.0f };
	Vector2f m_Velocity{ 0.0f, 0.0f };
	Vector2f m_Gravity{ 0.0f, -981.0f };
	ActionState m_ActionState{ ActionState::moving };
	float m_AccuTransformSec{ 0.0f };
	float m_MaxTransformSec{ 1.0f };
	int m_Power{ 0 };

};

