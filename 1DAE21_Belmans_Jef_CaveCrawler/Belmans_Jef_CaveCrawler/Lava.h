#pragma once
#include "structs.h"

class Health;
class Avatar;

class Lava final
{
public:
	Lava(const Point2f& bottomLeft, float width, float height);
	~Lava() = default;
	Lava(const Lava& other) = delete;
	Lava& operator=(const Lava& other) = delete;
	Lava(Lava&& other) = delete;
	Lava& operator=(Lava&& other) = delete;

	void Update(Avatar& playerAvatar);
	void Draw() const;

private:
	Rectf m_BoxCollider;

	bool PlayerOverlapCheck(const Rectf& actorShape) const;
};