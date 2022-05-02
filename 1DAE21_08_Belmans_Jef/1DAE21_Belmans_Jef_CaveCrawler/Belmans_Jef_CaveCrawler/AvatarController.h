#pragma once
#include "pch.h"

class Vector2f;
class AvatarController
{
public:
	AvatarController(const Rectf& shape);
	AvatarController(const AvatarController& other) = delete;
	AvatarController& operator=(const AvatarController& other) = delete;
	AvatarController(AvatarController&& other) = delete;
	AvatarController& operator=(AvatarController&& other) = delete;
	~AvatarController() = default;

	void Move(const Vector2f& movement);

private:
	Rectf m_Shape;
};

