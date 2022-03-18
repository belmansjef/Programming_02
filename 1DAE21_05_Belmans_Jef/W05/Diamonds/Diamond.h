#pragma once
#include "pch.h"
#include "Vector2f.h"
#include <vector>

class Texture;
class Diamond
{
public:
	Diamond(const Point2f startPos);
	~Diamond();

	void Draw() const;
	void Update(float elapsedSec);
	void CheckIfClicked(Point2f clickPos);
	void Reset();

private:
	Texture* m_pTexture{};
	Point2f m_StartPos{};
	
	std::vector<Point2f> m_Vertices
	{ Point2f(24.0f, 48.0f)
	, Point2f(48.0f, 24.0f)
	, Point2f(24.0f, 0.0f)
	, Point2f(0.0f, 24.0f) };

	std::vector<Point2f> m_TransVertices
	{ m_Vertices[0]
	, m_Vertices[1]
	, m_Vertices[2]
	, m_Vertices[3] };

	Vector2f m_Translation{Vector2f()};
	float m_Rotation{0.0f};
	float m_Scale{1.0f};

	bool m_IsSelected{};
};

