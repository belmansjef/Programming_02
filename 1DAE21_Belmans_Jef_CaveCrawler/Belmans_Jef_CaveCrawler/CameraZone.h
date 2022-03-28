#pragma once
#include "pch.h"

class CameraZone final
{
public:
	CameraZone(float left, float bottom, float width, float height);
	~CameraZone() = default;
	CameraZone(const CameraZone& other) = delete;
	CameraZone& operator=(const CameraZone& other) = delete;
	CameraZone(CameraZone&& other) = delete;
	CameraZone& operator=(CameraZone&& other) = delete;

	bool IsInZone(const Rectf& actorShape) const;
	Rectf GetBoundaries() const;

private:
	Rectf m_Boundaries;
};

