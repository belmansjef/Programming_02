#pragma once
#include <math.h>
#include "utils.h"
#include "Texture.h"
#include "Sprite.h"

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
	Rectf m_Shape{ 50.0f, 40.0f, 13.0f, 14.0f };

	float m_Gravity{ -250.0f };
	float m_GravityScale{ 1.0f };

	Vector2f m_Velocity{ 0.0f, 0.0f };
	float m_MaxVelocity{ 700.0f };
	float m_Damping{ 1.0f };

	int m_MovementDirection{ 0 };
	int m_HorizontalScale{ 1 };
	int m_JumpInput{ 0 };
	float m_MovementSpeed{ 50.0f };
	float m_JumpHeight{ 5.0f };
	float m_InitialJumpVelocity{ 120.0f };

	void GetInput();
	void ProcessInput(float elapsedSec, const Level& level);

	void ClampVelocity();
	void DampVelocity(float elapsedSec);
};

