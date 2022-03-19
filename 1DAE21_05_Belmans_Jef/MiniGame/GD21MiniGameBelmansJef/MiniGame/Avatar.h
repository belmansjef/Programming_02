#pragma once
#include <math.h>
#include "utils.h"
#include "Texture.h"

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
	Texture* m_pSpritesTexture;
	Rectf m_Shape{ 50.0f, 280.0f, 72.0f, 97.0f };
	float m_ClipWidth{ 72.0f };
	float m_ClipHeight{ 97.0f };
	int m_NrOfFrames{ 10 };
	int m_NrFramesPerSec{ 10 };
	int m_AnimFrame{};
	float m_AnimTime{};

	float m_Gravity{ -981.0f };
	float m_GravityScale{ 1.0f };
	float m_Damping{ 1.0f };
	Vector2f m_Velocity{ 0.0f, 0.0f };
	float m_MaxVelocity{ 800.0f };

	float m_MovementSpeed{ 200.0f };
	float m_JumpHeight{ 5.0f };
	float m_InitialJumpVelocity{ 642.5f };

	ActionState m_ActionState{ ActionState::moving };
	float m_AccuTransformSec{ 0.0f };
	float m_MaxTransformSec{ 1.0f };
	int m_Power{ 0 };

	void UpdateWaitingState();
	void UpdateMovingState(float elapsedSec, const Level& level);
	void UpdateTransformingState(float elapsedSec);
	void UpdateAnimation(float elapsedSec);
	void ClampVelocity();
	void DampVelocity(float elapsedSec);
};

