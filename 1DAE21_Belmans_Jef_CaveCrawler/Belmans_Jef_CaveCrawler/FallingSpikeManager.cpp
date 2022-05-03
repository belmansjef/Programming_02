#include "FallingSpikeManager.h"
#include "FallingSpike.h"
#include "Avatar.h"

FallingSpikeManager::~FallingSpikeManager()
{
	for (FallingSpike* element : m_pItems)
	{
		delete element;
		element = nullptr;
	}
}

FallingSpike* FallingSpikeManager::AddItem(const Point2f& bottomLeft)
{
	m_pItems.push_back(new FallingSpike(bottomLeft));
	return m_pItems.back();
}

void FallingSpikeManager::Update(const Rectf& actorShape, const std::vector<std::vector<Point2f>>& verts)
{
	for (FallingSpike* element : m_pItems)
	{
		if (!element->IsDestroyed())
		{
			element->Update(actorShape);
		}
	}

	LevelOverlapCheck(verts);
	PlayerOverlapCheck(actorShape);
}

void FallingSpikeManager::Draw() const
{
	for (FallingSpike* element : m_pItems)
	{
		if (!element->IsDestroyed())
		{
			element->Draw();
		}
	}
}

void FallingSpikeManager::Reset()
{
	for (FallingSpike* element : m_pItems)
	{
		element->Reset();
	}
}

void FallingSpikeManager::PlayerOverlapCheck(const Rectf& actorShape) const
{
	for (FallingSpike* element : m_pItems)
	{
		if (element->IsOverlapping(actorShape) && !element->IsDestroyed())
		{
			Avatar::TakeDamage();
			element->Destroy();
		}
	}
}

void FallingSpikeManager::LevelOverlapCheck(const std::vector<std::vector<Point2f>>& verts) const
{
	for (std::vector<Point2f> poly : verts)
	{
		for (FallingSpike* element : m_pItems)
		{
			if (!element->IsDestroyed() && element->IsOverlapping(poly))
			{
				element->Destroy();
			}
		}
	}
}
