#include "DamageBlockManager.h"
#include "DamageBlock.h"
#include "Health.h"
#include "SVGParser.h"
#include "utils.h"
#include "Camera.h"
#include "Avatar.h"

DamageBlockManager::~DamageBlockManager()
{
	for (DamageBlock* block : m_pItems)
	{
		DeleteBlock(block);
	}
}

DamageBlock* DamageBlockManager::AddItem(const Point2f& bottomLeft)
{
	m_pItems.push_back(new DamageBlock(bottomLeft.x, bottomLeft.y));
	return m_pItems.back();
}

bool DamageBlockManager::AddItemsFromSvgFile(const std::string& filePath)
{
	std::vector<std::vector<Point2f>> vertices;
	SVGParser::GetVerticesFromSvgFile(filePath, vertices);

	if (vertices[0].empty()) return false; // Something went wrong, no points were loaded

	const int blockSize{ 8 };
	for (std::vector<Point2f> polygon : vertices)
	{
		const float width = utils::GetDistance(polygon[1], polygon[2]);
		const float height = utils::GetDistance(polygon[2], polygon[3]);

		for (size_t i = 0; i < height / blockSize; i++)
		{
			for (size_t j = 0; j < width / blockSize; j++)
			{
				const Point2f bottomLeft
				{
					polygon[0].x + (blockSize * j),
					polygon[0].y + (blockSize * i)
				};

				AddItem(bottomLeft);
			}
		}
	}

	return true;
}

void DamageBlockManager::Draw() const
{
	for (DamageBlock* block : m_pItems)
	{
		block->Draw();
	}
}

void DamageBlockManager::Update(const Rectf& actorShape)
{
	for (DamageBlock* block : m_pItems)
	{
		block->Update();
	}

	PlayerCollisionCheck(actorShape);
}

void DamageBlockManager::PlayerCollisionCheck(const Rectf& acotrShape)
{
	for (DamageBlock* block : m_pItems)
	{
		if (block->IsOverlapping(acotrShape))
		{
			Avatar::TakeDamage();
		}
	}
}

void DamageBlockManager::DeleteBlock(const DamageBlock* block) const
{
	delete block;
	block = nullptr;
}
