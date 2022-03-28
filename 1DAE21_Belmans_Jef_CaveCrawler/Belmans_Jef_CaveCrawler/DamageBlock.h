#pragma once
#include "Sprite.h"

class DamageBlock
{
public:
	DamageBlock(float left, float bottom);
	DamageBlock(const DamageBlock& other) = delete;
	DamageBlock& operator=(const DamageBlock& other) = delete;
	DamageBlock(DamageBlock&& other) = delete;
	DamageBlock& operator=(DamageBlock&& other) = delete;
	~DamageBlock();

	bool IsOverlapping(const Rectf& rect);

	void Draw() const;
	void Update();

private:
	Sprite m_Sprite;
	Rectf m_Shape;
};

